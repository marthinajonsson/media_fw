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
    m_seriesMap.clear();
    m_movieMap.clear();
}

void JsonParser::add(const Category &category, DatabaseItem &item) {

    Json::Value add;
    add[TITLE] = item.getTitle();
    add[GENRE] = item.getGenre();
    add[DIRECTOR] = item.getDirector();
    for (const auto &a : item.getActors()) {
        add[ACTORS] = a;
    }

    if (category == Category::Movie) {
        m_root[ITEMS][MOVIES].append(add);
    }
    else {
        m_root[ITEMS][SERIES].append(add);
    }


    std::ofstream db_file("../data/db.json", std::ios::trunc);
    std::cout << m_root << std::endl;
    db_file << m_root;
    db_file.close();
}

void JsonParser::remove(const Category &_category, DatabaseItem &_item) {

    Json::Value remove;
    remove[TITLE] = _item.getTitle();
    remove[GENRE] = _item.getGenre();
    remove[DIRECTOR] = _item.getDirector();
    for (const auto &a : _item.getActors()) {
        remove[ACTORS] = a;
    }

    std::string cat = MOVIES;
    if(_category == Category::Series) { cat = SERIES; }

    for (Json::ArrayIndex i = 0; m_root[ITEMS][cat].isValidIndex(i); i++) {
        auto title = m_root[ITEMS][cat][i][TITLE].asString();
        auto genre = m_root[ITEMS][cat][i][GENRE].asString();
        auto director = m_root[ITEMS][cat][i][DIRECTOR].asString();
        auto actors = m_root[ITEMS][cat][i][ACTORS].asString();

        if(_item.getTitle() == title && _item.getDirector() == director) {
            m_root[ITEMS][cat].removeIndex(i, &remove);
        }
    }

    std::ofstream db_file("../data/db.json", std::ios::trunc);
    std::cout << m_root << std::endl;
    db_file << m_root;
    db_file.close();
}

/* TODO change so that what is loaded goes straight to Queue in MovieDatabase and that info is used.
 * not these maps.
 */
void JsonParser::load(const Category &category)
{
    Json::Value root;

    std::ifstream db_file("../data/db.json", std::ifstream::binary);
    db_file >> root;
    db_file.close();

    m_root = root;

    if(category == Category::Movie) {
        m_movieMap.clear();
        root = root[ITEMS][MOVIES];
        for (Json::ArrayIndex i = 0; root.isValidIndex(i); i++) {
            m_parsed.clear();
            auto title = root[i][TITLE].asString();
            auto genre = root[i][GENRE].asString();
            auto director = root[i][DIRECTOR].asString();
            auto actors = root[i][ACTORS].asString();
            auto path = root[i][PATH].asString();
            m_parsed.push_back(genre);
            m_parsed.push_back(director);
            m_parsed.push_back(path);
            auto result = split(actors, ',');
            for (const auto &s : result) {
                m_parsed.push_back(s);
            }
            m_movieMap[title] = m_parsed;
        }
    }
    else {
        m_seriesMap.clear();
        root = root[ITEMS][SERIES];
        for (Json::ArrayIndex i = 0; root.isValidIndex(i); i++) {
            m_parsed.clear();
            auto title = root[i][TITLE].asString();
            auto genre = root[i][GENRE].asString();
            auto director = root[i][DIRECTOR].asString();
            auto actors = root[i][ACTORS].asString();

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

bool JsonParser::find(Category &category, const std::string &val)
{
    m_resultMap.clear();
    bool result = false;
    auto map = getMovieParsed();
    if(category == Category::Series) { map = m_seriesMap; }

    for (auto it: map) {
        std::vector<std::string>::iterator p_it;
        temp_title = it.first;
        auto props = it.second;

        if(temp_title != val)
        {
            p_it = std::find(it.second.begin(), it.second.end(), val);

            if(p_it == it.second.end())
            {
                continue;
            }
        }

        std::vector<std::string> vec;
        vec.push_back(temp_title);
        vec.insert(vec.end(), it.second.begin(), it.second.end());
        m_resultMap.insert(std::pair(temp_title, vec));
        result = true;
    }
    return result;
}
