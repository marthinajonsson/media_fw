//
// Created by mjonsson on 10/3/18.
//



#ifndef MEDIAFW_DATABASE_H
#define MEDIAFW_DATABASE_H

/*
 *  The purpose of this module is to work as an interface for subclasses and let them perform database actions
 * */

#include "DatabaseItem.h"

#include <string>
#include <queue>
#include <iostream>

class Database {
public:
    Database() = default;
    ~Database() = default;


    virtual void pushItem(DatabaseItem _item){};

    virtual DatabaseItem fetchItem(int id) {};

    virtual int getNumberOfItem(){};

    enum Pattern {
        TITLE = 4,
        ACTOR,
        GENRE = 2,
        DIRECTOR
    };

protected:
    std::queue<DatabaseItem> _items;
};


#endif //MEDIAFW_DATABASE_H
