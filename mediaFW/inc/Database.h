//
// Created by mjonsson on 10/3/18.
//

#ifndef MEDIAFW_DATABASE_H
#define MEDIAFW_DATABASE_H

//#ifndef MEDIAFW_DATABASEITEM_H
#include "DatabaseItem.h"

#include <string>
#include <queue>
#include <iostream>

class Database {
public:
    Database() = default;
    ~Database() = default;
    std::queue<DatabaseItem> _items;

    virtual void pushItem(DatabaseItem _item){}

    virtual DatabaseItem fetchItem(int id) {}

    enum Pattern {
        TITLE = 4,
        ACTOR,
        GENRE = 2,
        DIRECTOR
    };
};


#endif //MEDIAFW_DATABASE_H
