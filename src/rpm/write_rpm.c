/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 1995-2001 Red Hat Software
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
#include <string.h>
#include <unistd.h>

#define PATH "/tmp/test.rpm"

static void lead(const char *rpmPath, const char *rpmName) 
{
    FILE *fptr = NULL;
    char buf[96] = { '\0' };
    int i;

    fptr = fopen(rpmPath, "ab");
    if (fptr == NULL)
        goto exit;

    buf[0] = 0xed;  //
    buf[1] = 0xab;  //
    buf[2] = 0xee;  //
    buf[3] = 0xdb;  // magic number

    buf[4] = 0x03;  // 
    buf[5] = 0x00;  // rpm version

    buf[6] = 0x00;  //
    buf[7] = 0x00;  // binary rpm

    buf[8] = 0x00;  //
    buf[9] = 0x01;  // architecture
    
    for (i = 0; i < 66 && i < strlen(rpmName); i++)
        buf[i + 9] = rpmName[i];
    
    buf[76] = 0x00; //
    buf[77] = 0x01; // osnum, Linux here is

    buf[78] = 0x00; //
    buf[79] = 0x05; // signature_type

    fwrite(buf, sizeof(buf), 1, fptr);
    fflush(fptr);

exit:
    if (fptr) {
        fclose(fptr);
        fptr = NULL;
    }
}

static void signature(const char *rpmPath, const char *Signature) 
{
    FILE *fptr = NULL;

    fptr = fopen(rpmPath, "ab");
    if (fptr == NULL)
        goto exit;
    char buf[] = { 0x8e, 0xad, 0xe8, 0x01, 0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x54,
                   0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x07,
                   0x00, 0x00, 0x10, 0x44, 0x00, 0x00, 0x00, 0x10,
                   0x00, 0x00, 0x01, 0x0d, 0x00, 0x00, 0x00, 0x06,
                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                   0x00, 0x00, 0x03, 0xec, 0x00, 0x00, 0x00, 0x07,
                   0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x10,
                   0x00, 0x00, 0x03, 0xef, 0x00, 0x00, 0x00, 0x04,
                   0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01,
                   0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x07,
                   0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x10, 0x00
                    };
    fwrite(buf, sizeof(buf), 1, fptr);
    fflush(fptr);

exit:
    if (fptr) {
        fclose(fptr);
        fptr = NULL;
    }
}

int main(int argc, char *argv[]) 
{
    printf("DEBUG: sizeof(char): %ld\n", sizeof(char));
    printf("DEBUG: sizeof(short): %ld\n", sizeof(short));
    
    unlink(PATH);

    lead(PATH, "test-0.1.0-1");
    signature(PATH, NULL);

    return 0;
}
