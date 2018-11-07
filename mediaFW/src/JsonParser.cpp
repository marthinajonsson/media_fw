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


bool JsonParser::find(const std::string &type, const std::string &val)
{
    m_resultMap.clear();
    bool result = false;
    bool foundTitle = false;
    std::string category = "movie";
    auto allMaps = {m_seriesMap, m_movieMap}; // this will be a hazard if the map is big
    for(auto mapToTest : allMaps) {
        for (auto it: mapToTest) {

            temp_title = it.first;
            auto props = it.second;
            if(temp_title != val)
            {
                auto found = std::find(it.second.begin(), it.second.end(), val);
                if(found == it.second.end()) {
                    continue;
                }
            }

            if(m_seriesMap == mapToTest) {
                category = "series";
            }
            std::vector<std::string> vec;
            vec.push_back(temp_title);
            vec.insert(vec.end(), it.second.begin(), it.second.end());
            vec.push_back(category);
            m_resultMap[temp_title] = vec;
            result = true;
        }
    }
    return result;
}

