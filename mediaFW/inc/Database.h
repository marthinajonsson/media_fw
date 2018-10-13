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
        std::cout << "Database constructor" << std::endl;
        syncDatabase();
    }
    ~Database() = default;

    void syncDatabase() {

        JsonParser json;
        json.parser();
        m_saved = json.getParsed();

        for(auto s : m_saved) {
            std::string title = s.first;
            std::string genre = s.second[0];
            std::string director = s.second[1];
            //s.second.erase(s.second.begin(), s.second.begin());
            std::vector<std::string> actors;
            for(auto a : s.second) {
                actors.push_back(a);
                std::cout << "sec " << a << std::endl;
            }
            DatabaseItem newItem {actors, title, genre, director};
            pushItem(newItem);
        }


    }

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

protected:
    std::queue<DatabaseItem> m_items;
    std::map<std::string, std::vector<std::string>>  m_saved;
    mutable std::mutex m_lock;
    std::condition_variable m_emptyQueue;
};


#endif //MEDIAFW_DATABASE_H
