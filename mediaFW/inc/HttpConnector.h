//
// Created by mjonsson on 11/16/18.
//

#ifndef MEDIAFW_HTTPCONNECTOR_H
#define MEDIAFW_HTTPCONNECTOR_H

#include <string>
#include "Request.h"
#include "StatusLogger.h"
#include "Util.h"

class HttpConnector {

public:
    Map<Event, Vec<std::string>> m_mapMethod;

    HttpConnector() : m_logger(new StatusLogger) {

        map_init(m_mapMethod)
                (Event::UPLOAD, {"uploadMovie", "uploadTvShow"})
                (Event::DOWNLOAD, {"downloadMovie", "downloadTvShow"})
                (Event::SEARCH, {"searchMovie", "searchTvShow"})
                (Event::DELETE, {"deleteMovie", "deleteTvShow"})
                (Event::STREAM, {"playMovie", "playTvShow"})
                ;
    }
    ~HttpConnector() = default;

    std::string compile(Request&);
    void send(Request&);

private:
    StatusLogger *m_logger;
    std::string m_name;
    std::string m_pwd;
    std::string m_server;
    std::string m_port;

    pid_t ch_pid;
    int status;

    std::string compileLogin();
    std::string compilePayload(Request&);


    Vec<std::string> uploadProperties {"filename"};
    Vec<std::string> downloadProperties {"title"};
    Vec<std::string> searchProperties {"title", "genre", "director", "actor"};
    Vec<std::string> deleteProperties {"title"};
    Vec<std::string> playProperties {"title", "id"};

};

#endif //MEDIAFW_HTTPCONNECTOR_H
