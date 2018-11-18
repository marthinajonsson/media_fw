//
// Created by mjonsson on 10/12/18.
//
//

#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <JsonParser.h>
#include <Util.h>

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

    if(category == Category::Movie || category == Category::Series) {

        std::ifstream db_file("../data/db.json", std::ifstream::binary);
        db_file >> root;
        db_file.close();
        m_root = root;

        m_mediaMap.clear();
        if(category == Category::Series) {
            root = root[ITEMS][SERIES];
        }else {
            root = root[ITEMS][MOVIES];
        }

        for (Json::ArrayIndex i = 0; root.isValidIndex(i); i++) {
            metadata m;
            m.s_title = root[i][TITLE].asString();
            m.s_genre = root[i][GENRE].asString();
            m.s_director = root[i][DIRECTOR].asString();
            m.s_category = category;
            auto actors = root[i][ACTORS].asString();

            auto result = split(actors, ',');
            for (const auto &s : result) {
                m.s_actors.push_back(s);
            }
            m_mediaMap[m.s_title] = m;
        }
    }
    else if (category == Category::Config) {
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

    for (auto it: map) {
        auto props = it.second;

        if(val != props.s_title || val != props.s_genre || val != props.s_director) {

            auto actor_it = std::find(it.second.s_actors.begin(), it.second.s_actors.end(), val);

            if(actor_it == it.second.s_actors.end())
            {
                continue;
            }
        }
        m_resultMap.insert(std::pair(it.second.s_title, it.second));
        result = true;
    }
    return result;
}
