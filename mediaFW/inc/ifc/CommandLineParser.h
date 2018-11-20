//
// Created by mjonsson on 11/8/18.
//

#ifndef MEDIAFW_COMMANDLINEPARSER_H
#define MEDIAFW_COMMANDLINEPARSER_H

#include <Request.h>

class CommandLineParser {
public:
    virtual Request process() = 0;
    virtual Request process(std::string &) = 0;
    virtual int interprete(std::vector<std::string> &, Request&) = 0;
};

#endif //MEDIAFW_COMMANDLINEPARSER_H
