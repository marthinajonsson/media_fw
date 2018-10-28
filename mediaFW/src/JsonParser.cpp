//
// Created by mjonsson on 10/12/18.
//
//

#include "JsonParser.h"
#include "json/json.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>



std::vector<std::string> JsonParser::split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

void JsonParser::clearMap() {
    m_seriesMap.clear();
    m_movieMap.clear();
}

void JsonParser::load()
{
    Json::Value root;
    std::ifstream db_file("../data/db.json", std::ifstream::binary);
    db_file >> root;
    m_movieMap.clear();
    m_seriesMap.clear();

    for (Json::ArrayIndex i = 0; root["items"]["Movies"].isValidIndex(i); i++) {
        m_parsed.clear();
        auto title = root["items"]["Movies"][i]["title"].asString();
        auto genre = root["items"]["Movies"][i]["genre"].asString();
        auto director = root["items"]["Movies"][i]["director"].asString();
        auto actors = root["items"]["Movies"][i]["actors"].asString();

        m_parsed.push_back(genre);
        m_parsed.push_back(director);

        auto result = split(actors, ',');
        for (const auto &s : result) {
            m_parsed.push_back(s);
        }
        m_movieMap[title] = m_parsed;
    }

    for (Json::ArrayIndex i = 0; root["items"]["Series"].isValidIndex(i); i++) {
        m_parsed.clear();
        auto title = root["items"]["Series"][i]["title"].asString();
        auto genre = root["items"]["Series"][i]["genre"].asString();
        auto director = root["items"]["Series"][i]["director"].asString();
        auto actors = root["items"]["Series"][i]["actors"].asString();

        m_parsed.push_back(genre);
        m_parsed.push_back(director);

        auto result = split(actors, ',');
        for (const auto &s : result) {
            m_parsed.push_back(s);
        }
        m_seriesMap[title] = m_parsed;
    }
    db_file.close();
}


bool JsonParser::find(const std::string &category, const std::string &pattern) {

    if(category == MOVIE) {
        for (auto it: m_movieMap) {
            if(it.first == pattern)
            {
                return true;
            }
            std::vector<std::string> vectorn = it.second;
            for (auto &it2 : vectorn) {
                if(it2 == pattern) {
                    return true;
                }
            }
        }
    }
    else {
        for (const auto &it : m_seriesMap) {
            if(it.first == pattern) { return true; }
            std::vector<std::string> vectorn = it.second;
            for (auto &it2 : vectorn) {
                if(it2 == pattern) { return true; }
            }
        }
    }
    return false;
}

