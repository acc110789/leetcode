/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2016 Leslie Zhai <xiang.zhai@i-soft.com.cn>
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

#include <iostream>
#include "sim_dict.h"

int main(int argc, char* argv[]) 
{
    CSIMDict *dict = new CSIMDict;
    TWCHAR wword[1024] = { '\0' };
    const CSIMDict::TState *state;
    FILE *fp = NULL;

    dict->parseText("dict.txt");
    fp = fopen("dict.txt", "r");
    dict->PrintOut(fp);
    MBSTOWCS(wword, argv[1] ? argv[1] : "孙", sizeof(wword));
    dict->matchLongest(dict->getRoot(), state, wword);
    if (state) {
        std::cout << state->word_id << std::endl;
    }

    if (dict) {
        delete dict;
        dict = NULL;
    }

    if (fp) {
        fclose(fp);
        fp = NULL;
    }
    return 0;
}
