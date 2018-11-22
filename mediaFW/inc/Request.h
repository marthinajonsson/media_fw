#include <utility>

//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_REQUEST_H
#define MEDIAFW_REQUEST_H

#include <map>
#include <algorithm>
#include "Util.h"
#include "Metadata.h"

class Request {
private:
    std::string UNDEF = "UNDEFINED";
    Metadata meta;
    int m_error;
    std::string m_errDesc;

    /*! \property event
     *  @brief mapped to @enum Event
     */
    Event m_event;

    /*! \property filename
     *
     */
    std::string m_filename;

    /*! \property progress
     *  @brief mapped to @enum Progress
     */
    Progress m_progess;

    Map<std::string, Property> m_propertyMap;

    /*! \property multipleResult
     *  @brief in case operation result in multiple items such in a Event::SEARCH
     *  the result is being saved
     */
    Map<std::string, Metadata> m_multipleResult;



public:
    Request(Event event, std::string &title, std::string &genre, std::string &director, Vec<std::string> &actors)
    {

        meta.m_title = title;
        meta.m_genre = genre;
        meta.m_director = director;
        meta.m_actors = actors;
        meta.m_category = Category::Undefined;
        m_event = event;
        m_error = RET::OK;
        m_progess = Todo;

        map_init(m_propertyMap)
                ("title", Property::TITLE_P)
                ("genre", Property::GENRE_P)
                ("director", Property::DIRECTOR_P)
                ("actor", Property::ACTORS_P)
                ;

    }

    const Request & operator = (const Request &t)
    {
        std::cout<<"Assignment operator called "<<std::endl;
        return t;
    }

    Request(Event event, std::string &title) : m_event(event)
    {
        meta.m_title = title;
        meta.m_category = Category::Undefined;
        m_error = RET::OK; m_progess = Todo;

        map_init(m_propertyMap)
                (TITLE, Property::TITLE_P)
                (GENRE, Property::GENRE_P)
                (DIRECTOR, Property::DIRECTOR_P)
                (ACTOR, Property::ACTORS_P)
                ;

    }

    explicit Request(Event event) : m_event(event) {
        m_progess = Todo;
        m_error = RET::OK;

        map_init(m_propertyMap)
                (TITLE, Property::TITLE_P)
                (GENRE, Property::GENRE_P)
                (DIRECTOR, Property::DIRECTOR_P)
                (ACTOR, Property::ACTORS_P)
                ;

    }


    Request(RET code, std::string desc) : m_error(code), m_errDesc(std::move(desc)) {
        m_progess = Todo;
        m_event = Event::UNDEFINED;

        map_init(m_propertyMap)
                (TITLE, Property::TITLE_P)
                (GENRE, Property::GENRE_P)
                (DIRECTOR, Property::DIRECTOR_P)
                (ACTOR, Property::ACTORS_P)
                ;

    }
    Request() {
        m_error = RET::OK;
        m_progess = Progress::Todo;
        m_event = Event::UNDEFINED;

        map_init(m_propertyMap)
                (TITLE, Property::TITLE_P)
                (GENRE, Property::GENRE_P)
                (DIRECTOR, Property::DIRECTOR_P)
                (ACTOR, Property::ACTORS_P)
                ;

    }

    ~Request() = default;

    /*
     * SET
     *
     * */

    void setEvent(Event e) { m_event = e; }
    void setCategory(const Category &cat) { meta.m_category = cat; }
    void setProgress(Progress progress) { m_progess = progress; }
    void setError(const int &err) { m_error = err; }
    void setErrorDesc(std::string desc) { m_errDesc = std::move(desc); }
    void setDirector(std::string director) { meta.m_director = std::move(director); }
    void setGenre(std::string genre) { meta.m_genre = std::move(genre); }
    void setTitle(std::string title) { meta.m_title = std::move(title); }
    void setActors(Vec<std::string> vec) { meta.m_actors = std::move(vec); }
    void setFilename(std::string filename) { m_filename = std::move(filename); }

    void setMultipleResult(Map<std::string, Metadata> map) { m_multipleResult = std::move(map); }

    void setProperty(std::string &type, std::string& val) {
        if(type.find(TITLE) != std::string::npos ) { this->meta.m_title = val; }
        else if(type.find(GENRE) != std::string::npos ) { this->meta.m_genre = val; }
        else if(type.find(DIRECTOR) != std::string::npos ) { this->meta.m_director = val; }
        else if (type.find(ACTOR) != std::string::npos ) { this->meta.m_actors.emplace_back(val); }
    }

    void setProperties(std::string t, std::string g, std::string d) {
        meta.m_title = std::move(t);
        meta.m_genre = std::move(g);
        meta.m_director = std::move(d);
    }

    /*
     *  GET
     *
     * */
    Metadata getMetadata() {
        return meta;
    }

    Map<std::string, Metadata>& getMultipleResult() {
        return m_multipleResult;
    }

    Map<std::string, std::string> getProperties() {
        Map<std::string, std::string> map;
        if(meta.m_title.find(UNDEF) == std::string::npos)
            map["title"] = meta.m_title;
        if(meta.m_genre.find(UNDEF) == std::string::npos)
            map["genre"] = meta.m_genre;
        if(meta.m_director.find(UNDEF) == std::string::npos)
            map["director"] = meta.m_director;
        if(!m_filename.empty())
            map["filename"] = m_filename;
        if(meta.m_actors.front().find(UNDEF) == std::string::npos)
            map["actor"] = meta.m_actors.front();
        return map;
    }

    Event getEvent() const {return m_event; }
    Progress getProgress() { return m_progess; }
    Category const getCategory() const { return meta.m_category; }

    int getError() { return m_error; }
    std::string getErrorDesc() { return m_errDesc; }
    std::string const getFileName() { return m_filename; }

};
#endif //MEDIAFW_REQUEST_H
