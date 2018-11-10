//
// Created by mjonsson on 10/16/18.
//



#ifndef MEDIAFW_UTIL_H
#define MEDIAFW_UTIL_H

#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>


enum RET {
    OK = 0,
    ERROR = -1
};

enum ORDER {
    TITLE_POS = 0,
    GENRE_POS = 1,
    DIRECTOR_POS = 2,
    ACTORS_POS = 3
};

enum Category {
    Movie = 0,
    Series = 1,
    All = 2
};

enum Progress {
    Todo,
    InProgress,
    Done
};

enum Event {
    UPLOAD = 0,
    DOWNLOAD = 1,
    SEARCH,
    DELETE,
    HELP,
    EXIT,
    UNDEFINED
};

template <typename T>
inline RET castTypeToRET( T& val ) {
    return static_cast<RET>(val);
}

template <typename T>
inline Event castTypeToEvent( T& val ) {
    return static_cast<Event>(val);
}

template <typename T>
inline Category castTypeToCategory( T& val ) {
    return static_cast<Category >(val);
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}

static std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

#endif //MEDIAFW_UTIL_H
