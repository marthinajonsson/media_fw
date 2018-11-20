//
// Created by mjonsson on 10/12/18.
//
//

#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <mutex>

#include "json/json.h"
#include "JsonParser.h"
#include "Util.h"


std::mutex single;
static JsonParser *instance;

JsonParser& JsonParser::getInstance()
{
    std::lock_guard<std::mutex> lock(single);
    if(!instance) {
        instance = new JsonParser();
    }
    return *instance;
}

std::vector<std::string> split(const std::string& s, char delimiter)
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

void JsonParser::clear() {
    m_mediaMap.clear();
}

void JsonParser::add(const Category &category, DatabaseItem &item) {
    Json::Value root;
    Json::Value add;
    std::ifstream db_read("../data/db.json", std::ifstream::binary);
    db_read >> root;
    db_read.close();
    add[TITLE] = item.getTitle();
    add[GENRE] = item.getGenre();
    add[DIRECTOR] = item.getDirector();
    for (const auto &a : item.getActors()) {
        add[ACTORS] = a;
    }

    if (category == Category::Movie) {
        root[ITEMS][MOVIES].append(add);
    }
    else {
        root[ITEMS][SERIES].append(add);
    }


    std::ofstream db_write("../data/db.json", std::ios::trunc);
    std::cout << root << std::endl;
    db_write << root;
    db_write.close();
}

void JsonParser::remove(const Category &_category, DatabaseItem &_item) {

    Json::Value remove;
    Json::Value root;
    std::ifstream db_read("../data/db.json", std::ifstream::binary);
    db_read >> root;
    db_read.close();
    remove[TITLE] = _item.getTitle();
    remove[GENRE] = _item.getGenre();
    remove[DIRECTOR] = _item.getDirector();
    for (const auto &a : _item.getActors()) {
        remove[ACTORS] = a;
    }

    std::string cat = MOVIES;
    if(_category == Category::Series) { cat = SERIES; }

    for (Json::ArrayIndex i = 0; root[ITEMS][cat].isValidIndex(i); i++) {
        auto title = root[ITEMS][cat][i][TITLE].asString();
        auto genre = root[ITEMS][cat][i][GENRE].asString();
        auto director = root[ITEMS][cat][i][DIRECTOR].asString();
        auto actors = root[ITEMS][cat][i][ACTORS].asString();

        if(_item.getTitle() == title && _item.getDirector() == director) {
            root[ITEMS][cat].removeIndex(i, &remove);
        }
    }

    std::ofstream db_write("../data/db.json", std::ios::trunc);
    std::cout << root << std::endl;
    db_write << root;
    db_write.close();
}


void JsonParser::load(Category category)
{
    Json::Value root;
    Category cat = category;
    if(cat == Category::Movie || cat == Category::Series) {

        std::ifstream db_file("../data/db.json", std::ifstream::binary);
        db_file >> root;
        db_file.close();

        m_mediaMap.clear();
        if(cat == Category::Series) {
            root = root[ITEMS][SERIES];
        }else {
            root = root[ITEMS][MOVIES];
        }

        for (Json::ArrayIndex i = 0; root.isValidIndex(i); i++) {
            auto t = root[i][TITLE].asString();
            auto g = root[i][GENRE].asString();
            auto d = root[i][DIRECTOR].asString();

            auto actors = root[i][ACTORS].asString();
            Metadata meta(t, g, d, cat);
            auto result = split(actors, ',');
            meta.m_actors = result;
            m_mediaMap.insert(std::pair(t, meta));
        }
    }
    else if (cat == Category::Config) {
        std::ifstream db_file("../data/config.json", std::ifstream::binary);
        db_file >> root;
        db_file.close();
        JsonParser::config c;
        m_configMap.clear();
        c.s_url = root["url"].asString();
        c.s_port = root["port"].asString();
        c.s_user = root["user"].asString();
        c.s_pwd = root["pwd"].asString();
        m_configMap["config"] = c;
    }
}

bool JsonParser::find(Category &category, const std::string &val)
{
    m_resultMap.clear();
    bool result = false;

    auto map = getLatestResult();

    for (auto it : map) {
        auto t = it.second.m_title;
        auto g = it.second.m_genre;
        auto d = it.second.m_director;
        auto a = it.second.m_actors;
        if(val != t && val != g && val != d) {

            auto actor_it = std::find(a.begin(), a.end(), val);

            if(actor_it == a.end())
            {
                continue;
            }
        }
        m_resultMap.insert(std::pair(t, it.second));
        result = true;
    }
    return result;
}
