//
// Created by mjonsson on 10/12/18.
//

#ifndef MEDIAFW_JSONPARSER_H
#define MEDIAFW_JSONPARSER_H

#include <iostream>
#include <vector>
#include <map>
#include <database/DatabaseItem.h>
#include <json/json.h>
#include <ifc/Parser.h>

class JsonParser : Parser {
public:
    static JsonParser& getInstance()
    {
        static JsonParser instance;
        return instance;
    }
    JsonParser() = default;

    JsonParser(JsonParser const&) = delete;
    void operator=(JsonParser const&) = delete;

    ~JsonParser() = default;

    void clear() override;
    void load(Category &category) override;
    void add(Category &category, DatabaseItem &item) override;
    void remove(Category &category, DatabaseItem &item) override;
    bool find(const std::string &type, const std::string &val) override;


    std::vector<std::string> getItem(Category &category) {
        auto map = m_movieMap;
        if(category == Category::Series) {
            map = m_seriesMap;
        }

        std::vector<std::string> item;
        item.push_back(temp_title);
        auto vec = map.at(temp_title);
        item.insert(item.end(), vec.begin(), vec.end());
        return item;
    }

    std::map<std::string, std::vector<std::string>> getMovieParsed() { return  m_movieMap; }
    std::map<std::string, std::vector<std::string>> getSeriesParsed() { return  m_seriesMap; }

private:
    Json::Value m_root;
    std::string temp_title;
    std::vector<std::string> m_parsed;
    std::map<std::string, std::vector<std::string>> m_movieMap;
    std::map<std::string, std::vector<std::string>> m_seriesMap;
};

#endif //MEDIAFW_JSONPARSER_H
