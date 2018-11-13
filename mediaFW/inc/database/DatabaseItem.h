//
// Created by mjonsson on 10/3/18.
//

/// <summary>
/// A module representing the content of a database item.
/// </summary>

#ifndef MEDIAFW_DATABASEITEM_H
#define MEDIAFW_DATABASEITEM_H

#include <string>
#include <vector>

#include "Request.h"
#include "Util.h"

class DatabaseItem{
public:

    DatabaseItem () = default;
    DatabaseItem(std::vector<std::string> &_actors, std::string &_title, std::string &_genre, std::string &_director, Category &_cat)
        : m_actors(_actors), m_title(_title), m_genre(_genre), m_director(_director), m_category(_cat)
    {
    };

    ~DatabaseItem() = default;

    /*! \public
     * @property Set
     * @param feature object of @class Request
     */
    void setFeature(Request feature){
        this->m_category = feature.getCategory();
        this->m_actors = feature.getActors();
        this->m_director = feature.getDirector();
        this->m_title = feature.getTitle();
        this->m_genre = feature.getGenre();
    };

    /*! \public getActors
     * @property Get
     * @return vector of actors @var m_actors
     */
    std::vector<std::string> getActors(){ return m_actors;}
    /*! \public getTitle
     * @property Get
     * @return string @var m_title
     */
    std::string getTitle() const { return m_title;}
    /*! \public getDirector
     * @property Get
     * @return string @var m_director
     */
    std::string getDirector(){ return m_director;}
    /*! \public getGenre
     * @property Get
     * @return string of m_genre
     */
    std::string getGenre(){ return m_genre;}
    /*! \public getDir
     * @property Get
     * @return string of m_directory
     */
    std::string getDir(){ return m_directory;}
    /*! \public getCategory
     * @property Get
     * @return @var m_category
     */
    Category getCategory() { return m_category; }

private:
    /*! \var m_Category
     * @brief movie or series see @enum Category
     */
    Category m_category;
    /*! \var m_directory
     * @brief not used at the moment
     */
    std::string m_directory;
    /*! \var m_title
     */
    std::string m_title;
    /*! \var m_genre
     *
     */
    std::string m_genre;
    /*! \var m_director
     *
     */
    std::string m_director;
    /*! \var m_actors
     * @brief vector of actor names
     */
    std::vector<std::string> m_actors;
};



#endif //MEDIAFW_DATABASEITEM_H
