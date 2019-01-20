//
// Created by mjonsson on 11/19/18.
//

#ifndef MEDIAFW_METADATA_H
#define MEDIAFW_METADATA_H

#include <string>
#include <vector>

#ifndef MEDIAFW_UTIL_H
#include "Util.h"
#endif

class Metadata {
public:

    Metadata (std::string &t, std::string &g, std::string &d, std::vector<std::string> &a, const Category &c) :
    m_title(t), m_genre(g), m_director(d), m_actors(a), m_category(c){

    }
    Metadata (std::string &t, std::string &g, std::string &d, const Category &c) :
            m_title(t), m_genre(g), m_director(d), m_category(c){

    }

    const Metadata & operator = (const Metadata &t)
    {
        std::cout<<"Assignment operator called "<<std::endl;
        return t;
    }


    Metadata() = default;
    ~Metadata() = default;

    std::string m_title = "UNDEFINED";
    std::string m_genre = "UNDEFINED";
    std::string m_director = "UNDEFINED";
    Vec<std::string> m_actors = {"UNDEFINED"};

    Category m_category = Category::Undefined;
};

#endif //MEDIAFW_METADATA_H
