//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_REQUEST_H
#define MEDIAFW_REQUEST_H

#include <map>
#include "Util.h"
#include "Metadata.h"

class Request {

    Metadata* meta;

    std::string UNDEF = "undefined";
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

    /*! \property multipleResult
     *  @brief in case operation result in multiple items such in a Event::SEARCH
     *  the result is being saved
     */
    std::map<std::string, Metadata> m_multipleResult;

public:
    Request(Event _event, const std::string _title, const std::string _genre, const std::string _director, const std::vector<std::string> _actors)
    {

        meta = new Metadata(_title, _genre, _director, _actors, Category::All);
        m_event = _event;
        m_error = RET::OK;
        m_progess = Todo;
    }

    Request(Event _event, std::string _title) : m_event(_event)
    {
        meta = new Metadata(_title, UNDEF, UNDEF, Category::All);
        m_error = RET::OK; m_progess = Todo;
    }

    explicit Request(Event _event) : m_event(_event) {
        m_progess = Todo;
        m_error = RET::OK;
        meta = new Metadata(UNDEF, UNDEF, UNDEF, Category::All);
    }


    Request(const int code, const std::string desc) : m_error(code), m_errDesc(desc) {
        m_progess = Todo;
        m_event = Event::UNDEFINED;
        meta = new Metadata(UNDEF, UNDEF, UNDEF, Category::All);
    }
    Request() {
        meta = new Metadata(UNDEF, UNDEF, UNDEF, Category::All);
        m_error = RET::OK;
        m_progess = Progress::Todo;
        m_event = Event::UNDEFINED;
    }

    ~Request() {
        delete meta;
    };


    void setEvent(Event e) { m_event = e; }
    void setCategory(const Category &cat) {
        meta->setCategory(cat);
    }
    void setDirector(const std::string &director) { meta->setDirector(director); }
    void setGenre(const std::string &genre) { meta->setGenre(genre); }
    void setTitle(const std::string &title) { meta->setTitle(title); }
    void setProgress(Progress progress) { m_progess = progress; }
    void setErrorDesc(const std::string &desc) { m_errDesc = desc; }
    void setError(const int &_err) { m_error = _err; }
    void setActors(const std::vector<std::string> &vec) { meta->setActors(vec); }
    void setFilename(const std::string &filename) { m_filename = filename; }
    void setMultipleResult(const std::map<std::string, Metadata> &map) { m_multipleResult = map; }

    int getError() { return m_error; }
    std::string getErrorDesc() { return m_errDesc; }
    Event getEvent() const {return m_event; }
    Progress getProgress() { return m_progess; }
    std::string const getFileName() { return m_filename; }
    std::string const getTitle() { return meta->getTitle(); }
    std::string const getGenre() { return meta->getGenre(); }
    std::string const getDirector() { return meta->getDirector(); }
    std::vector<std::string> const getActors() { return meta->getActors(); }
    Category const getCategory() const { return meta->getCategory(); }

    std::map<std::string, std::string> getProperties() {
        std::map<std::string, std::string> map;
        if(!meta->getTitle().empty())
            map["title"] = meta->getTitle();
        if(!meta->getGenre().empty())
            map["genre"] = meta->getGenre();
        if(!meta->getDirector().empty())
            map["director"] = meta->getDirector();
        if(!m_filename.empty())
            map["filename"] = m_filename;
        if(!meta->getActors().empty())
            map["actor"] = meta->getActors().front();
        return map;
    }

    void setProperties(const std::string& t, const std::string &g, const std::string &d) {
        meta->setProperties(t, g, d);
    }

    std::map<std::string, Metadata>& getMultipleResult() { return m_multipleResult; }

};
#endif //MEDIAFW_REQUEST_H
