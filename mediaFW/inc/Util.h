//
// Created by mjonsson on 10/16/18.
//



#ifndef MEDIAFW_UTIL_H
#define MEDIAFW_UTIL_H

#include <sstream>
#include <string>
#include <vector>
#include <assert.h>


enum RET { OK = 0, ERROR = -1};

enum ORDER {TITLE_POS = 0, GENRE_POS = 1, DIRECTOR_POS = 2, ACTORS_POS = 3};
enum Category { Movie = 0, Series = 1 };

const std::string MOVIE = "movie";
const std::string SERIES = "series";

const std::vector <std::string> VALID_CAT = { MOVIE, SERIES };

inline RET castIntToRET( int val ) {
    return static_cast<RET>(val);
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}

enum class Event { UPLOAD = 0, DOWNLOAD = 1, SEARCH, DELETE, HELP, EXIT };

const std::string DOWNLOAD = "download";
const std::string UPLOAD = "upload";
const std::string SEARCH = "search";
const std::string DELETE = "delete";
const std::string EXIT = "exit";
const std::string HELP = "help";

const std::vector<std::string> VALID = {UPLOAD, DOWNLOAD, SEARCH, DELETE, HELP, EXIT};

inline Event mapIntToEnum( long val ) {
    return static_cast<Event>(val);
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


const std::string TITLE = "title";
const std::string GENRE = "genre";
const std::string ACTOR = "actor";
const std::string DIRECTOR = "director";
const std::string FILENAME = "filename";

#endif //MEDIAFW_UTIL_H
