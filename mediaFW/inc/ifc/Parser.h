//
// Created by mjonsson on 11/3/18.
//

#ifndef MEDIAFW_PARSER_H
#define MEDIAFW_PARSER_H

#include <string>

#include <database/DatabaseItem.h>
#include "Util.h"

class Parser {
public:

    virtual void load(Category &category) = 0;
    virtual void clear() = 0;
    virtual bool find(const std::string &category, const std::string &type, std::string &value) = 0;
    virtual void add(Category &category, DatabaseItem &item) = 0;
    virtual void remove(Category &category, DatabaseItem &item) = 0;
};

#endif //MEDIAFW_PARSER_
