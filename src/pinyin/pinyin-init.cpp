// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

#ifndef __PINYIN_INIT__
#define __PINYIN_INIT__

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

    // FIXME: 需要判斷一下是否是漢字
    // 0x7F 是ASCII（非扩展）表最后一个字符
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

int main(int argc, char* argv[]) 
{
    PinYinInit* objPinYinInit = new PinYinInit;

    std::cout << "澀兔子 " << objPinYinInit->getInitials("澀兔子") << std::endl;
    std::cout << "の " << objPinYinInit->getInitials("の") << std::endl;
    std::cout << "Leslie " << objPinYinInit->getInitials("Leslie") << std::endl;

    delete objPinYinInit;
    objPinYinInit = nullptr;
    
    return 0;
}
