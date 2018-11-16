//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_REQUEST_H
#define MEDIAFW_REQUEST_H

#include <map>
#include "Util.h"

class Request {
public:
    Request(Event _event, std::string &_title, std::string, std::string &_genre, std::string &_director, std::vector<std::string> &_actors) :
        m_event(_event), m_title(_title), m_genre(_genre), m_director(_director), m_actors(_actors) { m_error = RET::OK; m_progess = Todo; }

    Request(Event _event, std::string &_title) : m_event(_event), m_title(_title) { m_error = RET::OK; m_progess = Todo; }

    Request(Event _event) : m_event(_event) {
        m_progess = Todo;
    }


    Request(const int code, const std::string desc) : m_error(code), m_errDesc(desc) {
        m_progess = Todo;
    }
    Request() {}

    ~Request() = default;

    void setEvent(Event e) { m_event = e; }
    void setCategory(Category cat) { m_category = cat; }
    void setProgress(Progress progress) { m_progess = progress; }
    void setErrorDesc(const std::string &_desc) { m_errDesc = _desc; }
    void setError(const int &_err) { m_error = _err; }
    void setTitle (const std::string &_title) { m_title = _title; }
    void setGenre(const std::string &_genre) { m_genre = _genre; }
    void setDirector(const std::string &_director) { m_director = _director; }
    void setActors(const std::vector<std::string> &_vec) { m_actors = _vec; }
    void setFilename(const std::string &_filename) { m_filename = _filename; }
    void setMultipleResult(const std::map<std::string, std::vector<std::string>> &_map) { m_multipleResult = _map; }

    int getError() { return m_error; }
    std::string getErrorDesc() { return m_errDesc; }
    Event getEvent() const {return m_event; }
    Progress getProgress() { return m_progess; }
    std::string const getFileName() { return m_filename; }
    std::string const getTitle() const { return m_title; }
    std::string const getGenre() { return m_genre; }
    std::string const getDirector() { return m_director; }
    std::vector<std::string> const getActors() { return m_actors; }
    Category const getCategory() const { return m_category; }

    std::vector<std::string> m_properties = {"title", m_title, "genre", m_genre, "director", m_director, "actor", m_actors.front(), "filename", m_filename};
    std::map<std::string, std::vector<std::string>> getMultipleResult() { return m_multipleResult; }

private:
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

    /*! \property title
     *
     */
    std::string m_title;

    /*! \property genre
     *
     */
    std::string m_genre;

    /*! \property director
     *
     */
    std::string m_director;

    /*! \property category
     *  @brief mapped to @enum Category
     */
    Category m_category;

    /*! \property actors
     *
     */
    std::vector<std::string> m_actors;

    /*! \property progress
     *  @brief mapped to @enum Progress
     */
    Progress m_progess;

    /*! \property multipleResult
     *  @brief in case operation result in multiple items such in a @enum Event::SEARCH
     *  the result is being saved
     */
    std::map<std::string, std::vector<std::string>> m_multipleResult;
};
#endif //MEDIAFW_REQUEST_H
