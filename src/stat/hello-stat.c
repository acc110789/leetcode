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

#include <glib.h>
#include <glib/gstdio.h>

int main(int argc, char *argv[]) 
{
    char *path = argv[1];
    struct stat buf;

    if (lstat(path, &buf) == -1) {
        printf("ERROR: failed to get %s lstat\n", path);
        return 0;
    }

    switch (buf.st_mode & S_IFMT) {
    case S_IFDIR:
        printf("DEBUG: line %d %s is directory\n", __LINE__, path);
        break;
    case S_IFLNK:
        printf("DEBUG: line %d %s is symbolic link\n", __LINE__, path);
        break;
    case S_IFREG:
        printf("DEBUG: line %d %s is regular file\n", __LINE__, path);
        break;
    default:
        break;
    }

    if (g_file_test(path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_SYMLINK))
        printf("DEBUG: line %d %s is symbolic link\n", __LINE__, path);

    return 0;
}
