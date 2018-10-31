//
// Created by mjonsson on 10/16/18.
//



#ifndef MEDIAFW_UTIL_H
#define MEDIAFW_UTIL_H

#include <string>
#include <vector>
enum RET { OK = 0, ERROR = -1};
enum class Event { UPLOAD = 0, DOWNLOAD = 1, SEARCH, DELETE, HELP, EXIT };

const std::string DOWNLOAD = "download";
const std::string UPLOAD = "upload";
const std::string SEARCH = "search";
const std::string DELETE = "delete";
const std::string EXIT = "exit";
const std::string HELP = "help";

const std::vector<std::string> VALID = {UPLOAD, DOWNLOAD, SEARCH, DELETE, HELP, EXIT};

inline Event mapIntToEnum( long val ) {
    return static_cast<Event >(val);
}


#endif //MEDIAFW_UTIL_H
