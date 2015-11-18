/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
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
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>

#include "md5.h"

static char *root_path = NULL;

static char *md5sum_file(char *path, char *md5sum) 
{
    unsigned char md5num[16] = { '\0' };

    if (md5_from_file(path, md5num) == -1) {
        printf("ERROR: failed to md5 from file %s\n", path);
        return NULL;
    }

    md5_num2str(md5num, md5sum);
    
    return md5sum;
}

static char *sys_path(char *path, char *sys) 
{
    char *pch = NULL;
    int i;

    if (root_path == NULL)
        return NULL;

    pch = strstr(path, root_path);
    if (pch == NULL)
        return NULL;

    for (i = 0; i < strlen(path); i++)
        sys[i] = path[strlen(root_path) + i];

    return sys;
}

static int file_exists(char *path) 
{
    struct stat buf;

    return stat(path, &buf);
}

static void traverse_dir(char *dir) 
{
    DIR *dp = NULL;
    struct dirent *ep;
    char path[PATH_MAX] = { '\0' };
    char md5sum[33] = { '\0' };
    char syspath[PATH_MAX] = { '\0' };

    dp = opendir(dir);
    if (dp) {
        while (ep = readdir(dp)) {
            struct stat buf;

            if (ep->d_name[0] != '.') {
                memset(path, 0, sizeof(path));
                snprintf(path, sizeof(path) - 1, "%s/%s", dir, ep->d_name);
                if (stat(path, &buf) == 0) {
                    if ((buf.st_mode & S_IFMT) == S_IFDIR) {
                        traverse_dir(path);
                    } else {
                        memset(md5sum, 0, sizeof(md5sum));
                        md5sum_file(path, md5sum);
                        printf("%s: %s\n", path, md5sum);
                        memset(syspath, 0, sizeof(syspath));
                        sys_path(path, syspath);
                        printf("%s: %s\n", 
                               syspath, 
                               file_exists(syspath) == 0 ? "exists" : "no exits");
                    }
                }
            }
        }
        closedir(dp);
        dp = NULL;
    }
}

int main(int argc, char *argv[]) 
{
    char *path = argv[1];
    struct stat buf;
    char md5sum[33] = { '\0' };

    printf("DEBUG: PATH_MAX %d\n", PATH_MAX);

    if (stat(path, &buf) == -1) {
        printf("ERROR: failed to get %s stat\n", path);
        return 0;
    }

    switch (buf.st_mode & S_IFMT) {
    case S_IFDIR:
        root_path = path;
        traverse_dir(path);
        break;
    case S_IFREG:
        md5sum_file(path, md5sum);
        printf("%s: %s\n", path, md5sum);
        break;
    default:
        break;
    }

    return 0;
}
