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
#include <fcntl.h>

#include <rpm/rpmdb.h>

int main(int argc, char *argv[]) 
{
    rpmdb db = NULL;

    openDatabase("/", "/var/lib/isoft-app", &db, O_RDONLY, 0644, 0);
    if (db == NULL) {
        printf("ERROR: failed to open rpm db\n");
        goto exit;
    }

exit:
    if (db) {
        rpmdbClose(db);
        db = NULL;
    }
    
    return 0;
}
