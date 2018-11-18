//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_REQUEST_H
#define MEDIAFW_REQUEST_H

#include <map>
#include "Util.h"

class Request {
public:
    Request(Event _event, std::string &_title, std::string, std::string &_genre, std::string &_director, std::vector<std::string> &_actors)
    {
        meta.s_title = _title;
        meta.s_genre = _genre;
        meta.s_director = _director;
        meta.s_actors =_actors;
        m_event = _event;
        m_error = RET::OK;
        m_progess = Todo;
    }

    Request(Event _event, std::string &_title) : m_event(_event)
    {
        m_error = RET::OK; m_progess = Todo;
        meta.s_title = _title;
    }

    Request(Event _event) : m_event(_event) {
        m_progess = Todo;
    }


    Request(const int code, const std::string desc) : m_error(code), m_errDesc(desc) {
        m_progess = Todo;
    }
    Request() {}

    ~Request() = default;


    void setEvent(Event e) { m_event = e; }
    void setCategory(Category cat) { meta.s_category = cat; }
    void setProgress(Progress progress) { m_progess = progress; }
    void setErrorDesc(const std::string &_desc) { m_errDesc = _desc; }
    void setError(const int &_err) { m_error = _err; }
    void setTitle (const std::string &_title) { meta.s_title = _title; }
    void setGenre(const std::string &_genre) {meta.s_genre = _genre; }
    void setDirector(const std::string &_director) { meta.s_director = _director; }
    void setActors(const std::vector<std::string> &_vec) { meta.s_actors = _vec; }
    void setFilename(const std::string &_filename) { m_filename = _filename; }
    void setMultipleResult(const std::map<std::string, struct metadata> _map) { m_multipleResult = _map; }

    int getError() { return m_error; }
    std::string getErrorDesc() { return m_errDesc; }
    Event getEvent() const {return m_event; }
    Progress getProgress() { return m_progess; }
    std::string const getFileName() { return m_filename; }
    std::string const getTitle() const { return meta.s_title; }
    std::string const getGenre() { return meta.s_genre; }
    std::string const getDirector() { return meta.s_director; }
    std::vector<std::string> const getActors() { return meta.s_actors; }
    Category const getCategory() const { return meta.category; }

    std::map<std::string, std::string> getProperties() {
        std::map<std::string, std::string> map;
        if(!meta.s_title.empty())
            map["title"] = meta.s_title;
        if(!meta.s_genre.empty())
            map["genre"] = meta.s_genre;
        if(!meta.s_director.empty())
            map["director"] = meta.s_director;
        if(!m_filename.empty())
            map["filename"] = m_filename;
        if(!meta.s_actors.empty())
            map["actor"] = meta.s_actors.front();
        return map;
    }


    std::map<std::string, struct metadata> getMultipleResult() { return m_multipleResult; }

private:
    metadata meta;
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
    std::map<std::string, metadata> m_multipleResult;


};
#endif //MEDIAFW_REQUEST_H
