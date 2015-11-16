/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright © 1994,1995 Ian Jackson <ian@chiark.greenend.org.uk>
 * Copyright © 2006-2014 Guillem Jover <guillem@debian.org>
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define LIBDPKG_VOLATILE_API
#include <dpkg/fdio.h>
#include <dpkg/ar.h>
#include <dpkg/dpkg.h>
#include <dpkg/error.h>
#include <dpkg/deb-version.h>
#include <dpkg/buffer.h>
#include <dpkg/compress.h>
#include <dpkg/subproc.h>
#include <dpkg/command.h>

#define DEBMAGIC            "debian-binary"
#define ADMINMEMBER         "control.tar"
#define DATAMEMBER          "data.tar"
#define TAR                 "tar"
#define OLDOLDDEBDIR        ".DEBIAN"
#define OLDDEBDIR           "DEBIAN"

enum dpkg_tar_options {
	DPKG_TAR_PASSTHROUGH = 0,
	DPKG_TAR_LIST = DPKG_BIT(0),
	DPKG_TAR_EXTRACT = DPKG_BIT(1),
	DPKG_TAR_PERMS = DPKG_BIT(2),
	DPKG_TAR_NOMTIME = DPKG_BIT(3),
};

static ssize_t read_line(int fd, char *buf, size_t min_size, size_t max_size)
{
    ssize_t line_size = 0;
    size_t n = min_size;

    while (line_size < (ssize_t)max_size) {
        ssize_t r;
        char *nl;

        r = fd_read(fd, buf + line_size, n);
        if (r <= 0)
            return r;

        nl = memchr(buf + line_size, '\n', r);
        line_size += r;

        if (nl != NULL) {
            nl[1] = '\0';
            return line_size;
        }

        n = 1;
    }

    buf[line_size] = '\0';
    return line_size;
}

static void DPKG_ATTR_NORET read_fail(int rc, const char *filename, const char *what)
{
    if (rc >= 0)
        ohshit("unexpected end of file in %s in %.255s",what,filename);
    else
        ohshite("error reading %s from file %.255s", what, filename);
}

static void movecontrolfiles(const char *thing) 
{
    char buf[200] = { '\0' };
    pid_t pid;

    snprintf(buf, sizeof(buf) - 1, "mv %s/* . && rmdir %s", thing, thing);
    pid = subproc_fork();
    if (pid == 0)
        command_shell(buf, "shell command to move files");

    subproc_reap(pid, "shell command to move files", 0);
}

int main(int argc, char *argv[]) 
{
    char cwd[PATH_MAX] = { '\0' };
    char *dir = NULL;
    enum dpkg_tar_options taroption = DPKG_TAR_EXTRACT | DPKG_TAR_NOMTIME;
    int admininfo = 0;
    char *debar = argv[1];
    int arfd = -1;
    struct stat stab;
    char versionbuf[40] = { '\0' };
    ssize_t r;
    off_t ctrllennum, memberlen = 0;
    bool header_done;
    char *infobuf = NULL;
    struct dpkg_error err;
    const char *errstr;
    struct deb_version version;
    int adminmember = -1;
    enum compressor_type decompressor = COMPRESSOR_TYPE_GZIP;
    char nlc;
    int dummy;
    int p1[2], p2[2];
    pid_t c1 = 0, c2, c3;
    int p2_out;

    if (getcwd(cwd, PATH_MAX)) {
        dir = m_malloc(PATH_MAX);
        snprintf(dir, PATH_MAX - 1, "%s/extract", cwd);
    }

    arfd = open(debar, O_RDONLY);
    if (arfd < 0)
        ohshite("failed to read archive %s", debar);
    if (fstat(arfd, &stab))
        ohshite("failed to fstat archive");

    r = read_line(arfd, 
                  versionbuf, 
                  strlen(DPKG_AR_MAGIC), 
                  sizeof(versionbuf) - 1);
    if (r < 0)
        read_fail(r, debar, "archive magic version number");

    if (strcmp(versionbuf, DPKG_AR_MAGIC) == 0) {
        ctrllennum = 0;
        header_done = false;
        for (;;) {
            struct ar_hdr arh;
        
            r = fd_read(arfd, &arh, sizeof(arh));
            if (r != sizeof(arh))
                read_fail(r, debar, "archive member header");

            dpkg_ar_normalize_name(&arh);

            if (dpkg_ar_member_is_illegal(&arh)) {
                ohshit("file '%.250s' is corrupt - bad archive header magic", 
                       debar);
            }

            memberlen = dpkg_ar_member_get_size(debar, &arh);
            if (!header_done) {
                infobuf = NULL;

                if (strncmp(arh.ar_name, DEBMAGIC, sizeof(arh.ar_name)) != 0) {
                    ohshit("file '%.250s' is not a debian binary archive "
                           "(try dpkg-split?)", debar);
                }

                infobuf = m_malloc(memberlen + 1);
                r = fd_read(arfd, infobuf, memberlen + (memberlen & 1));
                if (r != (memberlen + (memberlen & 1)))
                    read_fail(r, debar, "archive information header member");
                infobuf[memberlen] = '\0';

                if (strchr(infobuf, '\n') == NULL)
                    ohshit("archive has no newlines in header");

                errstr = deb_version_parse(&version, infobuf);
                if (errstr)
                    ohshit("archive has invalid format version: %s", errstr);
                if (version.major != 2) {
                    ohshit("archive is format version %d.%d; get a newer dpkg-deb",
                           version.major, version.minor);
                }

                if (infobuf) {
                    free(infobuf);
                    infobuf = NULL;
                }

                header_done = true;
            } else if (arh.ar_name[0] == '_') {
                if (fd_skip(arfd, memberlen + (memberlen & 1), &err) < 0) {
                    ohshit("cannot skip archive member from '%s': %s", 
                           debar, err.str);
                }
            } else {
				if (strncmp(arh.ar_name, ADMINMEMBER, strlen(ADMINMEMBER)) == 0) {
                    const char *extension = arh.ar_name + strlen(ADMINMEMBER);

	                adminmember = 1;
                    decompressor = compressor_find_by_extension(extension);
                    if (decompressor != COMPRESSOR_TYPE_NONE &&
                        decompressor != COMPRESSOR_TYPE_GZIP &&
                        decompressor != COMPRESSOR_TYPE_XZ) {
                        ohshit("ERROR: archive '%s' uses unknown compression "
                               "for member '%.*s', giving up", 
                               debar, (int)sizeof(arh.ar_name), arh.ar_name);
                    }
                } else {
                    if (adminmember != 1) {
                        ohshit("archive '%s' has premature member '%.*s' "
                               "before '%s', giving up",
                               debar, (int)sizeof(arh.ar_name), arh.ar_name, 
                               ADMINMEMBER);
                    }

	                if (strncmp(arh.ar_name, DATAMEMBER, strlen(DATAMEMBER)) == 0) {
	                    const char *extension = arh.ar_name + strlen(DATAMEMBER);

	                    adminmember = 0;
	                    decompressor = compressor_find_by_extension(extension);
                        if (decompressor == COMPRESSOR_TYPE_UNKNOWN) {
                            ohshit("archive '%s' uses unknown "
                                   "compression for member '%.*s', giving up",
                                   debar, (int)sizeof(arh.ar_name), arh.ar_name);
                        }
                    } else {
                        ohshit("archive '%s' has premature member '%.*s' "
                               "before '%s', giving up",
                               debar, (int)sizeof(arh.ar_name), arh.ar_name, DATAMEMBER);
                    }
                }
                if (adminmember == 1) {
                    if (ctrllennum != 0) {
                        ohshit("archive '%.250s' contains two control members, giving up",
                              debar);
                    }
                    ctrllennum = memberlen;
                }
                if (!adminmember != !admininfo) {
                    if (fd_skip(arfd, memberlen + (memberlen & 1), &err) < 0) {
                        ohshit("cannot skip archive member from '%s': %s", 
                               debar, err.str);
                    }
                } else {
                    break;
                }
            }
        }

        if (admininfo >= 2) {
            printf(" new debian package, version %d.%d.\n"
                   " size %jd bytes: control archive=%jd bytes.\n",
                   version.major, version.minor,
                   (intmax_t)stab.st_size, (intmax_t)ctrllennum);
            m_output(stdout, "<standard output>");
        }
    } else if (strncmp(versionbuf, "0.93", 4) == 0) {
        char ctrllenbuf[40] = { '\0' };
        int l;

        l = strlen(versionbuf);

        if (strchr(versionbuf, '\n') == NULL)
            ohshit("archive has no newlines in header");
        errstr = deb_version_parse(&version, versionbuf);
        if (errstr)
            ohshit("archive has invalid format version: %s", errstr);

        r = read_line(arfd, ctrllenbuf, 1, sizeof(ctrllenbuf));
        if (r < 0)
            read_fail(r, debar, "archive control member size");
        if (sscanf(ctrllenbuf, "%jd%c%d", &ctrllennum, &nlc, &dummy) != 2 || 
            nlc != '\n') {
            ohshit("archive has malformatted control member size '%s'", 
                   ctrllenbuf);
        }

        if (admininfo) {
            memberlen = ctrllennum;
        } else {
            memberlen = stab.st_size - ctrllennum - strlen(ctrllenbuf) - l;
            if (fd_skip(arfd, ctrllennum, &err) < 0) {
                ohshit("cannot skip archive control member from '%s': %s", 
                        debar, err.str);
            }
        }

        if (admininfo >= 2) {
            printf(" old debian package, version %d.%d.\n"
                   " size %jd bytes: control archive=%jd, main archive=%jd.\n",
                   version.major, version.minor,
                   (intmax_t)stab.st_size, (intmax_t)ctrllennum,
                   (intmax_t)(stab.st_size - ctrllennum - strlen(ctrllenbuf) - l));
            m_output(stdout, "<standard output>");
        }
    } else {
        if (strncmp(versionbuf, "!<arch>", 7) == 0) {
            notice("file looks like it might be an archive which has been\n"
                   " corrupted by being downloaded in ASCII mode");
        }

        ohshit("'%.255s' is not a debian format archive", debar);
    }

    m_pipe(p1);
    c1 = subproc_fork();
    if (!c1) {
        close(p1[0]);
        if (fd_fd_copy(arfd, p1[1], memberlen, &err) < 0)
            ohshit("cannot copy archive member from '%s' to decompressor pipe: %s",
             debar, err.str);
        if (close(p1[1]))
            ohshite("cannot close decompressor pipe");
        exit(0);
    }
    close(p1[1]);

    if (taroption) {
        m_pipe(p2);
        p2_out = p2[1];
    } else {
        p2_out = 1;
    }

    c2 = subproc_fork();
    if (!c2) {
        if (taroption)
            close(p2[0]);
        decompress_filter(decompressor, p1[0], p2_out,
                          "decompressing archive member");
        exit(0);
    }
    close(p1[0]);
    close(arfd);
    if (taroption) 
        close(p2[1]);

    if (taroption) {
        c3 = subproc_fork();
        if (!c3) {
            struct command cmd;

            command_init(&cmd, TAR, "tar");
            command_add_arg(&cmd, "tar");

            if ((taroption & DPKG_TAR_LIST) && (taroption & DPKG_TAR_EXTRACT))
                command_add_arg(&cmd, "-xv");
            else if (taroption & DPKG_TAR_EXTRACT)
                command_add_arg(&cmd, "-x");
            else if (taroption & DPKG_TAR_LIST)
                command_add_arg(&cmd, "-tv");
            else
                internerr("unknown or missing tar action '%d'", taroption);

        if (taroption & DPKG_TAR_PERMS)
            command_add_arg(&cmd, "-p");
        if (taroption & DPKG_TAR_NOMTIME)
            command_add_arg(&cmd, "-m");

        command_add_arg(&cmd, "-f");
        command_add_arg(&cmd, "-");
        command_add_arg(&cmd, "--warning=no-timestamp");

        m_dup2(p2[0],0);
        close(p2[0]);

        unsetenv("TAR_OPTIONS");

        if (dir) {
            if (chdir(dir)) {
                if (errno != ENOENT)
                    ohshite("failed to chdir to directory");

                if (mkdir(dir, 0777))
                    ohshite("failed to create directory");
                if (chdir(dir))
                    ohshite("failed to chdir to directory after creating it");
                }
            }

            command_exec(&cmd);
        }
        close(p2[0]);
        subproc_reap(c3, "tar", 0);
    }

    subproc_reap(c2, "<decompress>", SUBPROC_NOPIPE);
    if (c1 != -1)
        subproc_reap(c1, "paste", 0);
    if (version.major == 0 && admininfo) {
        while (version.minor && (version.minor % 10) == 0)
            version.minor /= 10;

        if (version.minor ==  931)
            movecontrolfiles(OLDOLDDEBDIR);
        else if (version.minor == 932 || version.minor == 933)
            movecontrolfiles(OLDDEBDIR);
    }

    return 0;
}
