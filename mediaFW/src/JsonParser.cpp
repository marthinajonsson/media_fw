//
// Created by mjonsson on 10/12/18.
//
//

#include "JsonParser.h"
#include "json/json.h"
#include "Util.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


void JsonParser::clear() {
    m_seriesMap.clear();
    m_movieMap.clear();
}

void JsonParser::add(Category &category, DatabaseItem &item) {

    Json::Value add;
    add["title"] = item.getTitle();
    add["genre"] = item.getGenre();
    add["director"] = item.getDirector();
    for (const auto &a : item.getActors()) {
        add["actors"] = a;
    }

    if (category == Category::Movie) {
        m_root["items"]["Movies"].append(add);
    }
    else {
        m_root["items"]["Series"].append(add);
    }


    std::ofstream db_file("../data/db.json", std::ios::trunc);
    std::cout << m_root << std::endl;
    db_file << m_root;
    db_file.close();
}

void JsonParser::remove(Category &category, DatabaseItem &item) {

    Json::Value remove;
    remove["title"] = item.getTitle();
    remove["genre"] = item.getGenre();
    remove["director"] = item.getDirector();
    for (const auto &a : item.getActors()) {
        remove["actors"] = a;
    }

    std::string cat = "Movies";
    if(category == Category::Series) { cat = "Series"; }

    for (Json::ArrayIndex i = 0; m_root["items"][cat].isValidIndex(i); i++) {
        auto title = m_root["items"][cat][i]["title"].asString();
        auto genre = m_root["items"][cat][i]["genre"].asString();
        auto director = m_root["items"][cat][i]["director"].asString();
        auto actors = m_root["items"][cat][i]["actors"].asString();

        if(item.getTitle() == title && item.getDirector() == director) {
            m_root["items"][cat].removeIndex(i, &remove);
        }
    }

    std::ofstream db_file("../data/db.json", std::ios::trunc);
    std::cout << m_root << std::endl;
    db_file << m_root;
    db_file.close();
}

void JsonParser::load(Category &category)
{
    Json::Value root;

    std::ifstream db_file("../data/db.json", std::ifstream::binary);
    db_file >> root;
    db_file.close();

    m_root = root;

    if(category == Category::Movie) {
        m_movieMap.clear();
        root = root["items"]["Movies"];
        for (Json::ArrayIndex i = 0; root.isValidIndex(i); i++) {
            m_parsed.clear();
            auto title = root[i]["title"].asString();
            auto genre = root[i]["genre"].asString();
            auto director = root[i]["director"].asString();
            auto actors = root[i]["actors"].asString();

            m_parsed.push_back(genre);
            m_parsed.push_back(director);

            auto result = split(actors, ',');
            for (const auto &s : result) {
                m_parsed.push_back(s);
            }
            m_movieMap[title] = m_parsed;
        }
    }
    else {
        m_seriesMap.clear();
        root = root["items"]["Series"];
        for (Json::ArrayIndex i = 0; root.isValidIndex(i); i++) {
            m_parsed.clear();
            auto title = root[i]["title"].asString();
            auto genre = root[i]["genre"].asString();
            auto director = root[i]["director"].asString();
            auto actors = root[i]["actors"].asString();

            m_parsed.push_back(genre);
            m_parsed.push_back(director);

            auto result = split(actors, ',');
            for (const auto &s : result) {
                m_parsed.push_back(s);
            }
            m_seriesMap[title] = m_parsed;
        }
    }
}


bool JsonParser::find(const std::string &category, const std::string &type, std::string &val)
{
    ulong genre = 0, director = 1; // indexes
    auto mapToTest = getMap(category);
    for (auto it: mapToTest) {
        std::vector<std::string> props = it.second;
        if(type == "title"){
            if(it.first == val)
            {
                return true;
            }
        }
        else if(type == "genre") {
            if(props.at(genre) == val){ return true; }
        }
        else if(type == "director") {
            if(props.at(director) == val) { return true; }
        }
        else if(type == "actor") {
            pop_front(props); // remove genre to ease search
            pop_front(props); // remove director to ease search
            for (auto &a : props){
                if(a == val) {
                    return true;
                }
            }
        }
    }

    return false;
}
