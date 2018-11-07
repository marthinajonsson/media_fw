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
        m_event(_event), m_title(_title), m_genre(_genre), m_director(_director), m_actors(_actors) , m_error(RET::OK)  {}

    Request(Event _event, std::string &_title) : m_event(_event), m_title(_title) , m_error(RET::OK) {}

    Request(Event _event) : m_event(_event), m_error() {}

    Request(int code) : m_error(code) {}

    ~Request() = default;

    void setCategory(Category &cat) { category = cat; }
    void setError(const int &_err) { m_error = _err; }
    void setTitle (const std::string &_title) { m_title = _title; }
    void setGenre(const std::string &_genre) { m_genre = _genre; }
    void setDirector(const std::string &_director) { m_director = _director; }
    void setActors(const std::vector<std::string> &_vec) { m_actors = _vec; }
    void setFilename(const std::string &_filename) { m_filename = _filename; }
    void setMultipleResult(const std::map<std::string, std::vector<std::string>> _map) { m_multipleResult = _map; }

    int getError() { return m_error; }
    Event getEvent() const {return m_event; }
    std::string const getFileName() { return m_filename; }
    std::string const getTitle() const { return m_title; }
    std::string const getGenre() { return m_genre; }
    std::string const getDirector() { return m_director; }
    std::vector<std::string> const getActors() { return m_actors; }
    Category const getCategory() const { return category; }
    std::map<std::string, std::vector<std::string>> getMultipleResult() { return m_multipleResult; }

private:
    int m_error;
    Event m_event;
    std::string m_filename;
    std::string m_title;
    std::string m_genre;
    std::string m_director;
    Category category;
    std::vector<std::string> m_actors;
    std::map<std::string, std::vector<std::string>> m_multipleResult;
};
#endif //MEDIAFW_REQUEST_H
