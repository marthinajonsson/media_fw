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
    void load(const Category &) override;
    void add(const Category &, DatabaseItem &) override;
    void remove(const Category &, DatabaseItem &) override;
    bool find(Category&, const std::string &) override;

    std::map<std::string, std::vector<std::string>> getMovieParsed() { return  m_movieMap; }
    std::map<std::string, std::vector<std::string>> getSeriesParsed() { return  m_seriesMap; }
    std::map<std::string, std::vector<std::string>> getLatestResult() { return  m_resultMap; }

private:

    const std::string TITLE = "title";
    const std::string GENRE = "genre";
    const std::string ACTORS = "actors";
    const std::string DIRECTOR = "director";
    const std::string ITEMS = "items";
    std::string MOVIES = "Movies";
    std::string SERIES = "Series";

    Json::Value m_root;
    std::string temp_title;
    std::vector<std::string> m_parsed;

    std::map<std::string, std::vector<std::string>> m_resultMap;
    std::map<std::string, std::vector<std::string>> m_movieMap;
    std::map<std::string, std::vector<std::string>> m_seriesMap;

};

#endif //MEDIAFW_JSONPARSER_H
