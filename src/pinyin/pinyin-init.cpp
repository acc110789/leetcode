/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2015 - 2016 Leslie Zhai <xiang.zhai@i-soft.com.cn>
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
#include <string>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <iconv.h>
#include <errno.h>

#ifndef __PINYIN_INIT__
#define __PINYIN_INIT__

// O(1) is super fast enough! so Chinese To Pinyin does not need to use Trie...
typedef std::unordered_map<std::string, std::string> PinYinArray;
typedef std::unordered_map<std::string, std::string>::iterator PinYinIter;

class PinYinInit 
{
public:
    explicit PinYinInit() 
    {
        std::string word, pinyin;
        double rate;
        unsigned int flag;

        m_file.open("rawdict_utf8_65105_freq.txt");
        while (m_file >> word >> rate >> flag >> pinyin) {
            if (word.size() > m_wordSize)
                continue;

            m_pinyins[word] = pinyin[0];
        }
        m_file.close();
    }

    ~PinYinInit() {}

    PinYinArray pinyins() const { return m_pinyins; }

    std::string getInitials(std::string str) 
    {
        std::string ret;
        
        for (unsigned int i = 0; i < str.size() / m_wordSize; i++) {
            std::string word = str.substr(i * m_wordSize, m_wordSize);
            printf("%x %x %x\n", word[0], word[1], word[2]);
            ret += m_pinyins[word];
        }

        return ret.size() ? ret : str;
    }

private:
    PinYinArray m_pinyins;
    std::ifstream m_file;
    const unsigned int m_wordSize = 3;
};

#endif // __PINYIN_INIT__

int iconv_helper(char *from, const char *fromcode, char *to, const char *tocode) 
{
    iconv_t cd = (iconv_t)-1;
    size_t from_size = -1;
    size_t to_size = -1;
    int ret = 0;

    cd = iconv_open(tocode, fromcode);
    if (cd == (iconv_t)-1) {
        std::cerr << "ERROR: " << strerror(errno) << std::endl;
        return -1;
    }

    from_size = strlen(from);
    to_size = sizeof(to) - 1;
    if (iconv(cd, &from, &from_size, &to, &to_size) == -1) {
        std::cerr << "ERROR: " << from << " " << fromcode << " " << tocode << 
            " " << strerror(errno) << std::endl;
        ret = -1;
    }

    iconv_close(cd);
    cd = (iconv_t)-1;

    return ret;
}

// ASCII to Chinese
void a2c(char *c, int h8, int l8) 
{
    char g[3];
    g[0] = h8;
    g[1] = l8;
    g[2] = '\0';
    if (iconv_helper(g, "GB2312", c, "UTF-8") == -1) {
        memset(c, 0, strlen(c));
        if (iconv_helper(g, "GBK", c, "UTF-8") == -1) {
            memset(c, 0, strlen(c));
            iconv_helper(g, "BIG5", c, "UTF-8");
        }
    }
    std::cout << g << " " << c << std::endl;
}

// Chinese to ASCII
void c2a(const char *c, int *h8, int *l8) 
{
    char to[6] = { '\0' };

    if (iconv_helper((char *)c, "UTF-8", to, "GB2312") == -1) {
        memset(to, 0, sizeof(to));
        if (iconv_helper((char *)c, "UTF-8", to, "GBK") == -1) {
            memset(to, 0, sizeof(to));
            iconv_helper((char *)c, "UTF-8", to, "BIG5");
        }
    }
    *h8 = (unsigned char)to[0];
    *l8 = (unsigned char)to[1];
    std::cout << c << " " << to << " " << *h8 << " " << *l8 << std::endl;
}

int main(int argc, char* argv[]) 
{
    int h8, l8;
    char to[6] = { '\0' };
    a2c(to, 181, 212);
    c2a(argv[1] ? argv[1] : "孙", &h8, &l8);

    PinYinInit* objPinYinInit = new PinYinInit;

    std::cout << "澀兔子 " << objPinYinInit->getInitials("澀兔子") << std::endl;
    std::cout << "の " << objPinYinInit->getInitials("の") << std::endl;
    std::cout << "Leslie " << objPinYinInit->getInitials("Leslie") << std::endl;

    if (argv[1])
        std::cout << argv[1] << objPinYinInit->getInitials(argv[1]) << std::endl;

    delete objPinYinInit;
    objPinYinInit = nullptr;
    
    return 0;
}
