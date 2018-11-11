//
// Created by mjonsson on 10/16/18.
//

#ifndef MEDIAFW_MEDIAHANDLER_H
#define MEDIAFW_MEDIAHANDLER_H

#include <functional>
#include "database/Database.h"
#include "database/MovieDatabase.h"
#include "database/SeriesDatabase.h"
#include "Cli.h"
#include "Client.h"
#include "StatusLogger.h"


/*! \class MediaHandler - handle for a user instance
 * @brief Synchronizes information from server and database,
 * Implements observer pattern.
 */

class MediaHandler : public Observer{
public:

    Client *p_client;

    MediaHandler () = default;

    MediaHandler(Category &category) : m_logger(new StatusLogger), p_cli(new Cli), p_conn(new Connection) {
        std::cout << "Mediahandler constructor" << std::endl;

        p_client = new Client(p_conn, p_cli);
        p_database = new MovieDatabase;
        p_client->registerObserver(this);
    };

    ~MediaHandler() {
        p_client->removeObserver(this);
        delete m_logger;
        delete p_cli;
        delete p_client;
        delete p_database;
        std::cout << "Deconstructor MediaHandler" << std::endl;
    };

    /*! \public MediaHandler::update
    * @brief receives new request from client
    * @implements observer method update
    * @param request
    * @return
    */
    int update(Request &request) override;


    void startCliThread() {
        int result = p_client->handleCliThread(); // will return when "exit" has been requested and block until then.
        if(result != 0) {
            m_logger->TRACE(Logger::ERR, "Client ended with error");
        }else {
            m_logger->TRACE(Logger::INFO, "Client ended normally");
        }
    }

    void startRequestThread() {
        int result = p_client->handleRequestThread();
        if(result != 0) {
            m_logger->TRACE(Logger::ERR, "Request thread ended with error");
        }else {
            m_logger->TRACE(Logger::INFO, "Request thread ended normally");
        }
    }

private:
    StatusLogger* m_logger;
    Connection *p_conn;
    Cli *p_cli;
    Database *p_database;

    enum class Status { DOWNLOADING = 0, UPLOADING, STREAMING = 2, SEARCHING, DELETING, IDLE, DISCONNECT } status;

    void syncDatabase(const Request &request);
    void getConnectionInfo(Event &event, Progress &progress);
    static Status updateDatabaseInfo(const Request &request);
};

#endif //MEDIAFW_MEDIAHANDLER_H
