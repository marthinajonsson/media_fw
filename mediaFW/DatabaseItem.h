//
// Created by mjonsson on 10/3/18.
//

#ifndef MEDIAFW_DATABASEITEM_H
#define MEDIAFW_DATABASEITEM_H


#include <string>
#include <vector>
struct Tag{
    std::string s_title;
    std::string s_genre;
    std::string s_director;
    std::vector<std::string> s_actors;
};

class DatabaseItem{
public:

    DatabaseItem()
    {
        this->id = 1;
    };

    ~DatabaseItem() = default;

    void setTag(Tag &&feature){
        this->m_actors = feature.s_actors;
        this->m_director = feature.s_director;
        this->m_title = feature.s_title;
        this->m_genre = feature.s_genre;
    };

    std::string gettitle(){ return m_title;}
    std::vector<std::string> getActors(){ return m_actors;}
    std::string getDirector(){ return m_director;}
    std::string getGenre(){ return m_genre;}
    std::string getDir(){ return directory;}

private:
    uint16_t id;
    std::string directory;
    std::string m_title;
    std::string m_genre;
    std::string m_director;
    std::vector<std::string> m_actors;
};



#endif //MEDIAFW_DATABASEITEM_H
