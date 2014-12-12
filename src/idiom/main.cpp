// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <random>

typedef std::string string_t;
typedef std::vector<string_t> array_t;
typedef std::map<string_t, array_t> dict_t;
typedef std::pair<string_t, array_t> pair_t;

static dict_t m_dict;
static std::ifstream m_file;

int main(int argc, char* argv[]) 
{
    std::mt19937 eng(time(NULL));
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

    string_t searchStr = search.substr(9, 12);
    std::cout << searchStr << std::endl;
    if (m_dict.find(searchStr) != m_dict.end()) {
        std::uniform_int_distribution<int> 
            uniform_int_index(0, m_dict[searchStr].size() - 1);
        std::cout << m_dict[searchStr][uniform_int_index(eng)] << std::endl;
    }

    return 0;
}
