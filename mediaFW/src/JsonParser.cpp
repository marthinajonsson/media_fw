//
// Created by mjonsson on 10/12/18.
//
//

#include "JsonParser.h"
#include "json/json.h"
#include "Util.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>


void JsonParser::clear() {
    m_seriesMap.clear();
    m_movieMap.clear();
}

void JsonParser::add(const Category &_category, DatabaseItem &_item) {

    Json::Value add;
    add["title"] = _item.getTitle();
    add["genre"] = _item.getGenre();
    add["director"] = _item.getDirector();
    for (const auto &a : _item.getActors()) {
        add["actors"] = a;
    }

    if (_category == Category::Movie) {
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

void JsonParser::remove(const Category &_category, DatabaseItem &_item) {

    Json::Value remove;
    remove["title"] = _item.getTitle();
    remove["genre"] = _item.getGenre();
    remove["director"] = _item.getDirector();
    for (const auto &a : _item.getActors()) {
        remove["actors"] = a;
    }

    std::string cat = "Movies";
    if(_category == Category::Series) { cat = "Series"; }

    for (Json::ArrayIndex i = 0; m_root["items"][cat].isValidIndex(i); i++) {
        auto title = m_root["items"][cat][i]["title"].asString();
        auto genre = m_root["items"][cat][i]["genre"].asString();
        auto director = m_root["items"][cat][i]["director"].asString();
        auto actors = m_root["items"][cat][i]["actors"].asString();

        if(_item.getTitle() == title && _item.getDirector() == director) {
            m_root["items"][cat].removeIndex(i, &remove);
        }
    }

    std::ofstream db_file("../data/db.json", std::ios::trunc);
    std::cout << m_root << std::endl;
    db_file << m_root;
    db_file.close();
}

void JsonParser::load(const Category &_category)
{
    Json::Value root;

    std::ifstream db_file("../data/db.json", std::ifstream::binary);
    db_file >> root;
    db_file.close();

    m_root = root;

    if(_category == Category::Movie) {
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

// TODO: type not used, check type with the position in vector
bool JsonParser::find(const std::string &_type, const std::string &_val)
{
    m_resultMap.clear();
    bool result = false;
    long typeInPos = getTypePosition(_type);
    auto allMaps = {m_seriesMap, m_movieMap}; // this will be a hazard if the map is big
    for(auto mapToTest : allMaps) {
        for (auto it: mapToTest) {
            std::vector<std::string>::iterator p_it;
            temp_title = it.first;
            auto props = it.second;
            if(temp_title != _val) // our val is not title
            {
                p_it = std::find(it.second.begin(), it.second.end(), _val); // find matches among properties instead
                if(p_it == it.second.end()) {
                    continue;
                }
            }

            std::vector<std::string> vec;
            if(mapToTest == m_seriesMap) {
                vec.push_back(SERIES);
            }
            else { vec.push_back(MOVIE); }
            vec.push_back(temp_title);
            vec.insert(vec.end(), it.second.begin(), it.second.end());
            m_resultMap[temp_title] = vec;
            result = true;
        }
    }
    return result;
}

