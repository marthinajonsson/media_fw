#include <utility>

//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_REQUEST_H
#define MEDIAFW_REQUEST_H

#include <map>
#include <algorithm>
#include <functional>
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

    Map<std::string, std::function<std::string()>> getCommands;

    Map<std::string, std::function<void(std::string&)>> setCommands;

    void setActor(std::string actor) {
        if(meta.m_actors.front() == UNDEF) {
            Vec<std::string> v2 = {actor};
            meta.m_actors.swap(v2);
        }
        else {
            meta.m_actors.emplace_back(std::move(actor));
        }
    }
    void setDirector(std::string director) { meta.m_director = std::move(director); }
    void setGenre(std::string genre) { meta.m_genre = std::move(genre); }
    void setTitle(std::string title) { meta.m_title = std::move(title); }
    void setFilename(std::string filename) { m_filename = std::move(filename); }

    std::string getTitle() {
        return meta.m_title;
    }
    std::string getGenre() {
        return meta.m_genre;
    }
    std::string getDirector() {
        return meta.m_director;
    }
    std::string getActor() {
        return meta.m_actors.front();
    }
    std::string getFilename() {
        return m_filename;
    }


    template<typename ftor>
    void install_getCommand(std::string name, ftor && handler)
    {
        getCommands.insert({
                                std::move(name),
                                std::forward<ftor>(handler)
                        });
    }
    template<typename ftor>
    void install_setCommand(std::string name, ftor && handler) {
        setCommands.insert({
                                   std::move(name),
                                   std::forward<ftor>(handler)
                           });
    }

    void mapper() {
        map_init(m_propertyMap)
                (TITLE, Property::TITLE_P)
                (GENRE, Property::GENRE_P)
                (DIRECTOR, Property::DIRECTOR_P)
                (ACTOR, Property::ACTORS_P)
                (PROGRESS, Property::PROGRESS_P)
                (CATEGORY, Property::CATEGORY_P)
                (EVENT, Property::EVENT_P)
                ;
    }

    void bindFunc() {
        std::function<std::string()> func = std::bind(&Request::getTitle, this);
        install_getCommand(TITLE, func);

        func = std::bind(&Request::getGenre, this);
        install_getCommand(GENRE, func);

        func = std::bind(&Request::getDirector, this);
        install_getCommand(DIRECTOR, func);

        func = std::bind(&Request::getActor, this);
        install_getCommand(ACTOR, func);

        func = std::bind(&Request::getFilename, this);
        install_getCommand(FILENAME, func);

        using std::placeholders::_1;
        std::function<void(std::string&)> foo = std::bind( &Request::setTitle, this, _1);
        install_setCommand(TITLE, foo);

        foo = std::bind( &Request::setGenre, this, _1);
        install_setCommand(GENRE, foo);

        foo = std::bind( &Request::setDirector, this, _1);
        install_setCommand(DIRECTOR, foo);

        foo = std::bind( &Request::setActor, this, _1);
        install_setCommand(ACTOR, foo);

        foo = std::bind( &Request::setFilename, this, _1);
        install_setCommand(FILENAME, foo);
    }

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
        mapper();
        bindFunc();
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
        mapper();
        bindFunc();
    }

    explicit Request(Event event) : m_event(event) {
        m_progess = Todo;
        m_error = RET::OK;
        mapper();
        bindFunc();
    }


    Request(RET code, std::string desc) : m_error(code), m_errDesc(std::move(desc)) {
        m_progess = Todo;
        m_event = Event::UNDEFINED;
        mapper();
        bindFunc();
    }

    Request() {
        m_error = RET::OK;
        m_progess = Progress::Todo;
        m_event = Event::UNDEFINED;
        mapper();
        bindFunc();

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

    void setActors(Vec<std::string> vec) { meta.m_actors = std::move(vec); }

    void setMultipleResult(Map<std::string, Metadata> map) { m_multipleResult = std::move(map); }

    void set(const std::string& cmd, std::string& value) {
        auto func = setCommands.at(cmd);
        func(value);
    }


    /*
     *  GET
     *
     * */
    Metadata getMetadata() {
        return meta;
    }

    std::string get(const std::string& cmd) {
        auto func = getCommands.at(cmd);
        return func();
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

};
#endif //MEDIAFW_REQUEST_H
