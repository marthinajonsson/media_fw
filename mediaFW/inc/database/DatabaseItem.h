//
// Created by mjonsson on 10/3/18.
//

/// <summary>
/// A module representing the content of a database item.
/// </summary>

#ifndef MEDIAFW_DATABASEITEM_H
#define MEDIAFW_DATABASEITEM_H

#include <string>
#include <vector>

#include "Request.h"
#include "Util.h"

class DatabaseItem{
public:

    DatabaseItem () = default;
    DatabaseItem(std::vector<std::string> &_actors, std::string &_title, std::string &_genre, std::string &_director, Category &_cat)
        : m_actors(_actors), m_title(_title), m_genre(_genre), m_director(_director), m_category(_cat)
    {
    };

    ~DatabaseItem() = default;

    void setFeature(Request feature){
        this->m_category = feature.category;
        this->m_actors = feature.m_actors;
        this->m_director = feature.m_director;
        this->m_title = feature.m_title;
        this->m_genre = feature.m_genre;
    };

    std::vector<std::string> getActors(){ return m_actors;}
    std::string getTitle() const { return m_title;}
    std::string getDirector(){ return m_director;}
    std::string getGenre(){ return m_genre;}
    std::string getDir(){ return directory;}
    Category getCategory() { return m_category; }

private:
    Category m_category;
    std::string directory;
    std::string m_title;
    std::string m_genre;
    std::string m_director;
    std::vector<std::string> m_actors;
};



#endif //MEDIAFW_DATABASEITEM_H
