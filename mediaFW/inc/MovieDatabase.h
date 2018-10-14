//
// Created by mjonsson on 10/4/18.
//

/*
 *  The purpose of this module is to work as an interface and help the client perform database actions
 * */

#ifndef MEDIAFW_MOVIEDATABASE_H
#define MEDIAFW_MOVIEDATABASE_H

#include "Database.h"
#include <algorithm>


class MovieDatabase : public Database {
public:

    void pushItem(const DatabaseItem &m_item) override {
        std::unique_lock<std::mutex> guard(m_lock);
        if(m_items.empty()) {
            m_emptyList.notify_one();
        }
        m_items.push_back(m_item);
    }

    DatabaseItem fetchItem(const std::string &title) override {
        std::unique_lock<std::mutex>  m_lock;
        if(m_items.empty()){
            std::cout << "Database is empty" << std::endl;
        }
        return m_items.front();
    }

    long getNumberOfItem() override {
        std::unique_lock<std::mutex>  m_lock;
        return m_items.size();
    }

    void purgeItem(const DatabaseItem &m_item) override {
        std::unique_lock<std::mutex>  m_lock;

        std::list<DatabaseItem>::iterator it;
        int index = 0;
        for (it = m_items.begin(); it != m_items.end(); ++it){
            if(it->getTitle() == m_item.getTitle()) {
                m_items.erase(it);
            }
            index++;
        }
    }

    void printAll() override
    {
        std::unique_lock<std::mutex>  m_lock;
        for(auto item : m_items) {
            std::cout << item.getTitle() << ", " << item.getGenre() << ", " << std::endl;
            for(const auto &s : item.getActors()) {
                std::cout << s << "\n" << std::endl;
            }
        }
    }
};


#endif //MEDIAFW_MOVIEDATABASE_H
