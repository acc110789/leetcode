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

#include <rpm/rpmio.h>
#include <rpm/header.h>

#include <glib.h>

int main(int argc, char *argv[]) 
{
    FD_t fd = NULL;
    off_t size = -1; 
    char *ptr = NULL;
    GList *package_list = NULL;
    Header hdr = NULL;
    char *Name = NULL;
    char *Version = NULL;
    char *Arch = NULL;
    int i;

    fd = Fopen(argv[1] ? argv[1] : "/data/download/base/pkglist.005-extra", "r");
    if (fd == NULL) {
        printf("ERROR: failed to open header file\n");
        goto exit;
    }
    Fseek(fd, 0, SEEK_END);
    size = Ftell(fd);
    printf("%ld\n", size);
    Fseek(fd, 0, SEEK_SET);

    if (size == -1)
        goto exit;
    ptr = malloc(size * sizeof(char));
    if (ptr == NULL) {
        printf("ERROR: failed to allocate memory\n");
        goto exit;
    }
    Fread(ptr, size, sizeof(char), fd);
    Fseek(fd, 0, SEEK_SET);
    for (i = 0; i < size; i++) {
        if (ptr[i] == 0xffffff8e) {
            hdr = headerRead(fd, HEADER_MAGIC_YES);
            if (hdr) {
                Name = headerGetAsString(hdr, RPMTAG_NAME);
                Version = headerGetAsString(hdr, RPMTAG_VERSION);
                Arch = headerGetAsString(hdr, RPMTAG_ARCH);
                printf("%s %s %s\n", Name, Version, Arch);

                headerFree(hdr);
                hdr = NULL;
            }
        }
    }

exit:
    if (fd) {
        Fclose(fd);
        fd = NULL;
    }

    if (ptr) {
        free(ptr);
        ptr = NULL;
    }

    return 0;
}
