//
// Created by mjonsson on 10/4/18.
//

/// <summary>
/// A module that implements the functionality of Database.h and helps the client to perform database actions.
/// </summary>

#ifndef MEDIAFW_MOVIEDATABASE_H
#define MEDIAFW_MOVIEDATABASE_H

#include <algorithm>

#include "ifc/Observer.h"
#include "Database.h"
#include "Client.h"

class MovieDatabase : public Database, public Observer {
public:

    Client m_client;
    MovieDatabase() {
        syncLocalDatabase();
    }

    explicit MovieDatabase (Client *p_client) {
        syncLocalDatabase();
        m_client = *p_client;
        m_client.registerObserver(this);
    }

    ~MovieDatabase() {
        m_client.removeObserver(this);
    }

    int update(Request &request) override {

        Progress p = request.getProgress();
        Event e = request.getEvent();

        if(Progress::InProgress == p) {
            std::cout << "Database awaits request" << std::endl;
            return RET::OK;
        }

        if(e == Event::UPLOAD) {
            DatabaseItem item;
            item.setFeature(request);
            pushItem(item);
        }
        else if(e == Event::DELETE) {
            DatabaseItem item;
            item.setFeature(request);
            purgeItem(item);
        }
        else if(e == Event::SEARCH) {
            auto title = request.getMetadata().m_title;
            fetchItem(title);
        }
        return RET::OK;
    }

    DatabaseItem fetchItemByKey(const std::string& key, const std::string &val) {
        std::unique_lock<std::mutex>  m_lock;
        if(m_items.empty()){
            std::cout << "Database is empty" << std::endl;
        }
        DatabaseItem noFound;
        std::list<DatabaseItem>::iterator it;
        for (it = m_items.begin(); it != m_items.end(); ++it){
            if(key == "title") {
                auto found = val.find(it->getTitle());
                if(std::string::npos != found) {
                    return *it;
                }
            }else if (key == "genre") {
                auto found = val.find(it->getGenre());
                if(std::string::npos != found) {
                    return *it;
                }

            }else if (key == "director") {
                auto found = val.find(it->getDirector());
                if(std::string::npos != found) {
                    return *it;
                }
            }
            else if (key == "actor") {
                for (const auto &act : it->getActors()) {
                    auto found = val.find(act);
                    if(std::string::npos != found) {
                        return *it;
                    }
                }
            }
        }
        return *it;
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

    bool isSame(DatabaseItem item, std::list<DatabaseItem>::iterator it) {
        return it->getTitle() == item.getTitle() &&
               it->getDirector() == item.getDirector();
    }

    /// <summary>
    /// Implementation for virtual member of Database.h
    /// Method that deletes the requested database item.
    /// </summary>
    /// <param>A const reference to a database item</param>
    void purgeItem(const DatabaseItem &m_item) override {
        std::unique_lock<std::mutex>  m_lock;
        std::list<DatabaseItem>::iterator it;
        std::list<DatabaseItem> temp_list;

        int numLoops = 1;
        // TODO m_items.end() does not work seem to be extended?
        for (it = m_items.begin(); it != m_items.end(); it++) {

            if(numLoops  > m_items.size()) { break; }

            if(it->getTitle() == m_item.getTitle()) {
                m_items.erase(it);
            }
            else {
                temp_list.push_back(*it);
            }
            numLoops++;
        }
        m_items = temp_list;
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
private:
    /*! \public syncLocalDatabase
     * @brief Reads local db.json and save to Database
     */
    void syncLocalDatabase() override {
        JsonParser::getInstance().load(Category::Movie);
        m_saved = JsonParser::getInstance().getLoaded();
        for(auto s : m_saved) {
            auto cat = s.second.m_category;
            DatabaseItem newItem {s.second.m_actors, s.second.m_title, s.second.m_genre, s.second.m_director, Category::Movie};
            pushItem(newItem);
        }

        JsonParser::getInstance().load(Category::Series);
        m_saved = JsonParser::getInstance().getLoaded();
        for(auto s : m_saved) {
            DatabaseItem newItem {s.second.m_actors, s.second.m_title, s.second.m_genre, s.second.m_director, Category::Series};
            pushItem(newItem);
        }
    }
};


#endif //MEDIAFW_MOVIEDATABASE_H
