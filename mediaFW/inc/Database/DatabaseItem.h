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

struct Tags{
    std::string s_title;
    std::string s_genre;
    std::string s_director;
    std::vector<std::string> s_actors;
};

class DatabaseItem{
public:

    DatabaseItem () {};
    DatabaseItem(std::vector<std::string> _actors, std::string _title, std::string _genre, std::string _director)
        : m_actors(_actors), m_title(_title), m_genre(_genre), m_director(_director)
    {
    };

    ~DatabaseItem() = default;

    void setFeature(Tags feature){
        this->m_actors = feature.s_actors;
        this->m_director = feature.s_director;
        this->m_title = feature.s_title;
        this->m_genre = feature.s_genre;
    };

    std::vector<std::string> getActors(){ return m_actors;}
    std::string getTitle() const { return m_title;}
    std::string getDirector(){ return m_director;}
    std::string getGenre(){ return m_genre;}
    std::string getDir(){ return directory;}

private:
    std::string directory;
    std::string m_title;
    std::string m_genre;
    std::string m_director;
    std::vector<std::string> m_actors;
};



#endif //MEDIAFW_DATABASEITEM_H
