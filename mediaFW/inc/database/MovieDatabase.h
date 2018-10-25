//
// Created by mjonsson on 10/4/18.
//

/// <summary>
/// A module that implements the functionality of Database.h and helps the client to perform database actions.
/// </summary>

#ifndef MEDIAFW_MOVIEDATABASE_H
#define MEDIAFW_MOVIEDATABASE_H

#include "Database.h"
#include <algorithm>


class MovieDatabase : public Database {
public:

    MovieDatabase () {
        syncLocalDatabase();
    }

    void syncLocalDatabase() override {

        JsonParser json;
        json.parser();
        m_saved = json.getParsed();

        for(auto s : m_saved) {
            std::string title = s.first;
            std::string genre = s.second[0];
            std::string director = s.second[1];
            std::vector<std::string> actors;

            for(auto it = s.second.begin() + 2; it != s.second.end(); ++it) {
                actors.push_back(*it);
            }

            DatabaseItem newItem {actors, title, genre, director};
            pushItem(newItem);
        }
    }

    /// <summary>
    /// Implementation for virtual member of Database.h
    /// Method that uploads the requested database item.
    /// </summary>
    /// <param>A const reference to a database item</param>
    /// <returns></returns>
    void pushItem(const DatabaseItem &m_item) override {
        std::unique_lock<std::mutex> guard(m_lock);
        if(m_items.empty()) {
            m_emptyList.notify_one();
        }
        m_items.push_back(m_item);
    }

    /// <summary>
    /// Implementation for virtual member of Database.h
    /// Method that fetches the requested database item.
    /// </summary>
    /// <param>A const reference to a title</param>
    /// <returns>The requested DatabaseItem</returns>
    DatabaseItem fetchItem(const std::string &title) override {
        std::unique_lock<std::mutex>  m_lock;
        if(m_items.empty()){
            std::cout << "Database is empty" << std::endl;
        }
        DatabaseItem noFound;
        std::list<DatabaseItem>::iterator it;
        for (it = m_items.begin(); it != m_items.end(); ++it){
            if(it->getTitle() == title) {
                noFound = *it;
                return noFound;
            }
        }
        return *it;
    }

    /// <summary>
    /// Implementation for virtual member of Database.h
    /// Method that return the size of the database.
    /// </summary>
    /// <returns>Size of the database (long).</returns>
    long getNumberOfItem() override {
        std::unique_lock<std::mutex>  m_lock;
        return m_items.size();
    }

    /// <summary>
    /// Implementation for virtual member of Database.h
    /// Method that deletes the requested database item.
    /// </summary>
    /// <param>A const reference to a database item</param>
    void purgeItem(DatabaseItem item) override {
        std::unique_lock<std::mutex>  m_lock;
        std::list<DatabaseItem>::iterator it;
        for (it = m_items.begin(); it != m_items.end(); ++it){
            if (it->getTitle() == item.getTitle()) {
                m_items.erase(it);
            }
        }
    }

    /// <summary>
    /// Implementation for virtual member of Database.h
    /// Method that prints the entire database content.
    /// </summary>
    void printAll() override
    {
        std::unique_lock<std::mutex>  m_lock;
        for(auto item : m_items) {
            std::string result = item.getTitle() + " " + item.getGenre() + " " + item.getDirector() + " ";
            for(const auto &s : item.getActors()) {
                result += s + " ";
            }
            std::cout << result << std::endl;
        }
    }
};


#endif //MEDIAFW_MOVIEDATABASE_H
