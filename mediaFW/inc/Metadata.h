//
// Created by mjonsson on 11/19/18.
//

#ifndef MEDIAFW_METADATA_H
#define MEDIAFW_METADATA_H

#include <string>
#include <vector>
#include "Util.h"

class Metadata {
public:

    Metadata (const std::string &t, const std::string &g, const std::string &d, const std::vector<std::string> &a, const Category &c) :
    m_title(t), m_genre(g), m_director(d), m_actors(a), m_category(c){

    }
    Metadata (const std::string &t, const std::string &g, const std::string &d, const Category &c) :
            m_title(t), m_genre(g), m_director(d), m_category(c){

    }
    Metadata() = default;
    ~Metadata() = default;

    std::string & getTitle() { return m_title; }
    std::string & getGenre() { return m_genre; }
    std::string & getDirector() { return m_director; }
    const Category& getCategory() { return m_category; }
    std::vector<std::string> & getActors() { return m_actors; }


    void setProperties(const std::string& t, const std::string& g, const std::string& d) {
        m_title = t;
        m_genre = g;
        m_director = d;
    }

    void setProperties(std::string& t, std::string& g, std::string& d, const Category &c) {
        m_title = t;
        m_genre = g;
        m_director = d;
        m_category = c;
    }
    void setCategory (const Category& category) { m_category = category; }
    void setActors(const std::vector<std::string>& actors) { m_actors = actors; }
    void setDirector(const std::string &director) { m_director = director; }
    void setGenre(const std::string &genre) { m_genre = genre; }
    void setTitle(const std::string &title) { m_title = title; }
private:
        std::string m_title;
        std::string m_genre;
        std::string m_director;
        std::string m_id;
        std::string m_year;
        Category m_category = Category::All;
        std::vector<std::string> m_actors;
};

#endif //MEDIAFW_METADATA_H
