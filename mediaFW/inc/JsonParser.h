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

    void load(Category &category) override;
    void clear() override;
    bool find(const std::string &category, const std::string &pattern) override;
    void add(Category &category, DatabaseItem &item) override;
    void remove(Category &category, DatabaseItem &item) override;
    std::map<std::string, std::vector<std::string>> getMovieParsed() { return  m_movieMap; }
    std::map<std::string, std::vector<std::string>> getSeriesParsed() { return  m_seriesMap; }

private:
    Json::Value m_root;
    std::vector<std::string> m_parsed;
    std::map<std::string, std::vector<std::string>> m_movieMap;
    std::map<std::string, std::vector<std::string>> m_seriesMap;

};

#endif //MEDIAFW_JSONPARSER_H
