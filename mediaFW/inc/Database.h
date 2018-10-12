//
// Created by mjonsson on 10/3/18.
//



#ifndef MEDIAFW_DATABASE_H
#define MEDIAFW_DATABASE_H

/*
 *  The purpose of this module is to work as an interface for subclasses and let them perform database actions
 * */

#include "DatabaseItem.h"
#include "JsonParser.h"

#include <string>
#include <queue>
#include <iostream>
#include <mutex>
#include <future>
#include <thread>

class Database {
public:

    Database() {
        json.parser();
        std::cout << "Database constructor" << std::endl;
    }
    ~Database() {
        std::cout << "Database deconstructor" << std::endl;
    };


    virtual void pushItem(DatabaseItem m_item){};   // DatabaseItem

    virtual DatabaseItem fetchItem(int id) {};

    virtual long getNumberOfItem(){};

    virtual void purgeItem(DatabaseItem m_item){};

    virtual void addItem(DatabaseItem m_item) {};

    enum Pattern {
        TITLE = 4,
        ACTOR,
        GENRE = 2,
        DIRECTOR
    };

    JsonParser json;

protected:
    std::queue<DatabaseItem> m_items;
    mutable std::mutex m_lock;
    std::condition_variable m_emptyQueue;
};


#endif //MEDIAFW_DATABASE_H
