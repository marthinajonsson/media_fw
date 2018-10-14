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
#include <list>
#include <iostream>
#include <mutex>
#include <future>
#include <thread>


class Database {
public:

    Database() {
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
            s.second.erase(s.second.begin(), s.second.begin()+2);
            std::vector<std::string> actors;
            for(auto a : s.second) {
                actors.push_back(a);
                std::cout << "sec " << a << std::endl;
            }
            DatabaseItem newItem {actors, title, genre, director};
            pushItem(newItem);
        }
    }

    virtual void pushItem(const DatabaseItem &m_item){};

    virtual DatabaseItem fetchItem(const std::string &title){};

    virtual void purgeItem(const DatabaseItem &m_item){};

    virtual void printAll(){};

    virtual long getNumberOfItem(){};


protected:
    std::list<DatabaseItem> m_items;
    std::map<std::string, std::vector<std::string>>  m_saved;
    mutable std::mutex m_lock;
    std::condition_variable m_emptyList;
};


#endif //MEDIAFW_DATABASE_H
