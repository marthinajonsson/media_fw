//
// Created by mjonsson on 10/12/18.
//

#ifndef MEDIAFW_JSONPARSER_H
#define MEDIAFW_JSONPARSER_H

#include <iostream>
#include <vector>
#include <map>

class JsonParser {
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

    void load();
    void clearMap();
    bool find(const std::string &category, const std::string &pattern);
    std::map<std::string, std::vector<std::string>> getMovieParsed() { return  m_movieMap; }
    std::map<std::string, std::vector<std::string>> getSeriesParsed() { return  m_seriesMap; }

private:
    std::vector<std::string> m_parsed;
    std::map<std::string, std::vector<std::string>> m_movieMap;
    std::map<std::string, std::vector<std::string>> m_seriesMap;

    std::vector<std::string> split(const std::string& s, char delimiter);

};


static const std::string MOVIE = "movie";
static const std::string SERIES = "series";
#endif //MEDIAFW_JSONPARSER_H
