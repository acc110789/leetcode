// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

typedef std::string string_t;
typedef std::vector<string_t> array_t;
typedef std::map<string_t, array_t> dict_t;
typedef std::pair<string_t, array_t> pair_t;

static dict_t m_dict;
static std::ifstream m_file;

int main(int argc, char* argv[]) 
{
    string_t line;
    string_t search(argv[1] ? argv[1] : "好好学习");
    const int WORD_SIZE = 12;

    if (argc < 2 || search.size() < WORD_SIZE) {
        std::cout << "Usage: ./idiom 好好学习" << std::endl;
        return 1;
    }
    
    m_file.open("dict.txt");
    while (m_file >> line) {
        if (line.size() < WORD_SIZE) continue;

        string_t lineFirstStr = line.substr(0, 3);
        if (m_dict.find(lineFirstStr) != m_dict.end()) {
            m_dict[lineFirstStr].push_back(line);
        } else {
            array_t words; words.push_back(line);
            m_dict[lineFirstStr] = words;
        }
    }
    m_file.close();
    std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << " " << m_dict.size() 
              << std::endl;

    string_t searchStr = search.substr(0, 3);
    if (m_dict.find(searchStr) != m_dict.end()) {
        std::cout << m_dict[searchStr][0] << std::endl;
    }

    return 0;
}
