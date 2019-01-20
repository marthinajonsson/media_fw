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
#include <Request.h>
#include <Util.h>

class DatabaseItem {
public:

    DatabaseItem () = default;
    DatabaseItem(Vec<std::string> &_actors, std::string &_title, std::string &_genre, std::string &_director, const Category &_cat)
        : m_actors(_actors), m_title(_title), m_genre(_genre), m_director(_director), m_category(_cat)
    {
    };

    ~DatabaseItem() = default;

    bool operator==(const DatabaseItem& rhs) {
        return m_title == rhs.m_title && m_genre == rhs.m_genre &&
    m_director == rhs.m_director && m_actors.front() == rhs.m_actors.front();
    }

    /*! \public
     * @property Set
     * @param feature object of @class Request
     */
    void setFeature(Request &feature){
        Metadata* meta = feature.getMetadata();
        this->m_category = feature.getCategory();
        this->m_actors = meta->m_actors;
        this->m_director = meta->m_director;
        this->m_title = meta->m_title;
        this->m_genre = meta->m_genre;
    };

    /*! \public getActors
     * @property Get
     * @return vector of actors @var m_actors
     */
    Vec<std::string> getActors(){ return m_actors;}
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
    Vec<std::string> m_actors;
};



#endif //MEDIAFW_DATABASEITEM_H
