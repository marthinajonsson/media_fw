//
// Created by mjonsson on 10/12/18.
//

#ifndef MEDIAFW_JSONPARSER_H
#define MEDIAFW_JSONPARSER_H

#include <iostream>
#include <vector>
#include <map>

#include <json/json.h>

#include "ifc/Subject.h"
#include <ifc/Parser.h>
#include <database/DatabaseItem.h>


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

    /*! \public clear
     * @brief clear @var m_movieMap and @var m_seriesMap
     */
    void clear() override;
    /*! \public load
     * @brief parses and saves information from db.json to m_movieMap and m_seriesMap
     * @param Category instance of @enum Category
     */
    void load(const Category &) override;
    /*! \public add
     * @brief adds database item to db.json
     * @param instance of @enum Category and an instance of @class DatabaseItem
     */
    void add(const Category &, DatabaseItem &) override;
    /*! \public remove
     * @brief removes database item from db.json
     * @param instance of @enum Category and an instance of @class DatabaseItem
     */
    void remove(const Category &, DatabaseItem &) override;
    /*! \public find
     * @brief check if search value exists in db.json
     * @return true or false
     */
    bool find(Category&, const std::string &) override;

    /*! \public getMovieParsed
     *
     * @return @var m_movieMap
     */
    std::map<std::string, std::vector<std::string>> getMovieParsed() { return  m_movieMap; }
    /*! \public getSeriesParsed
     *
     * @return @var m_seriesMap
     */
    std::map<std::string, std::vector<std::string>> getSeriesParsed() { return  m_seriesMap; }
    /*! \public getLatestResult
     * @brief returns latest result after find()
     * @return @var m_resultMap
     */
    std::map<std::string, std::vector<std::string>> getLatestResult() { return  m_resultMap; }


private:

    /*! \var TITLE "title"
     *
     */
    const std::string TITLE = "title";
    /*! \var GENRE "genre"
     *
     */
    const std::string GENRE = "genre";
    /*! \var ACTORS "actors"
     *
     */
    const std::string ACTORS = "actors";
    /*! \var DIRECTOR "director"
     *
     */
    const std::string DIRECTOR = "director";
    const std::string PATH = "path";
    /*! \var ITEMS "items"
     *
     */
    const std::string ITEMS = "items";
    /*! \var MOVIES "Movies"
     *
     */
    std::string MOVIES = "Movies";
    /*! \var SERIES "Series"
     *
     */
    std::string SERIES = "Series";

    Json::Value m_root;
    std::string temp_title;
    std::vector<std::string> m_parsed;

    /*! \var m_resultMap
     *
     */
    std::map<std::string, std::vector<std::string>> m_resultMap;
    /*! \var m_movieMap
     *
     */
    std::map<std::string, std::vector<std::string>> m_movieMap;
    /*! \var m_seriesMap
     *
     */
    std::map<std::string, std::vector<std::string>> m_seriesMap;

};

#endif //MEDIAFW_JSONPARSER_H
