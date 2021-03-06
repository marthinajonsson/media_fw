//
// Created by mjonsson on 11/3/18.
//

#ifndef MEDIAFW_PARSER_H
#define MEDIAFW_PARSER_H

#include <string>
#include <database/DatabaseItem.h>


class Parser {
public:

    virtual void clear() = 0;
    virtual void load(Category category) = 0;
    virtual void add(const Category &category, DatabaseItem &item) = 0;
    virtual void remove(const Category &category, DatabaseItem &item) = 0;
    virtual bool find(Category &category, const std::string &val) = 0;
};

#endif //MEDIAFW_PARSER_
