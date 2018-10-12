//
// Created by mjonsson on 10/4/18.
//

/*
 *  The purpose of this module is to work as an interface and help the client perform database actions
 * */

#ifndef MEDIAFW_MOVIEDATABASE_H
#define MEDIAFW_MOVIEDATABASE_H


#include "Database.h"


class MovieDatabase : public Database {
public:

    void pushItem(DatabaseItem m_item) override {
        std::unique_lock<std::mutex> guard(m_lock);
        if(m_items.empty()) {
            m_emptyQueue.notify_one();
        }
        m_items.push(m_item);
    }

    DatabaseItem fetchItem(int id) override {
        std::unique_lock<std::mutex>  (m_lock);
        if(m_items.empty()){
            std::cout << "Database is empty" << std::endl;
        }
        return m_items.front();
    }

    long getNumberOfItem() override {
        std::unique_lock<std::mutex>  (m_lock);
        return m_items.size();
    }

    void purgeItem(DatabaseItem m_item) override {

    }

    void addItem(DatabaseItem  m_item) override {

    }

private:

};


#endif //MEDIAFW_MOVIEDATABASE_H
