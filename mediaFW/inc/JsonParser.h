//
// Created by mjonsson on 10/12/18.
//

#ifndef MEDIAFW_JSONPARSER_H
#define MEDIAFW_JSONPARSER_H

#include <iostream>
#include <vector>
#include <map>
#include <mutex>

#include "Metadata.h"
#include "JsonUtils.h"
#include "ifc/Subject.h"
#include "ifc/Parser.h"


class JsonParser : Parser {
public:
    struct config {
        std::string s_url;
        std::string s_port;
        std::string s_user;
        std::string s_pwd;
    };

    static JsonParser& getInstance();
    JsonParser(JsonParser const&) = delete;
    void operator=(JsonParser const&) = delete;

    /*! \public clear
     * @brief clear @var m_movieMap and @var m_seriesMap
     */
    void clear() override;
    /*! \public load
     * @brief parses and saves information from db.json to m_movieMap and m_seriesMap
     * @param Category instance of @enum Category
     */
    void load(Category) override;
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

    /*! \public getConfig
     *
     * @return @var m_configMap
     */
    std::map<std::string, config> getConfig() { return  m_configMap; }

    /*! \public getLatestResult
     * @brief returns latest result after find()
     * @return @var m_mediaMap
     */
    std::map<std::string, Metadata> getLatestResult() { return  m_mediaMap; }

    std::map<std::string, Metadata> getLatestFilteredResult() { return  m_resultMap; }

private:

    JsonParser() = default;
    ~JsonParser() = default;

    /*! \var m_configMap
    *
    */
    std::map<std::string, config> m_configMap;

    /*! \var m_mediaMap
    *
    */
    std::map<std::string, Metadata> m_mediaMap;

    /*! \var m_mediaMap
    *
    */
    std::map<std::string, Metadata> m_resultMap;

    /*! \var ITEMS "items"
    *
    */
    const std::string ITEMS = "items";
    /*! \var MOVIES "Movies"
     *
     */
    const std::string MOVIES = "Movies";
    /*! \var SERIES "Series"
    *
    */
    const std::string SERIES = "Series";

};

#endif //MEDIAFW_JSONPARSER_H
