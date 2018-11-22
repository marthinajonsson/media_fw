//
// Created by mjonsson on 10/16/18.
//

#ifndef MEDIAFW_MEDIAHANDLER_H
#define MEDIAFW_MEDIAHANDLER_H

#include <functional>
#include "database/Database.h"
#include "database/MovieDatabase.h"
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
    Map<Event, const char*> m_eventMap;
    Map<Progress, const char*> m_progressMap;
    MediaHandler() : m_logger(new StatusLogger), p_conn(new Connection) {
        std::cout << "Mediahandler constructor" << std::endl;

        map_init(m_eventMap)
                (Event::UPLOAD, "[UPLOAD] ")
                (Event::DOWNLOAD, "[DOWNLOAD] ")
                (Event::SEARCH, "[SEARCH] ")
                (Event::DELETE, "[DELETE] ")
                (Event::EXIT, "[EXIT] ")
                ;


        map_init(m_progressMap)
                (Progress::Todo, "[TODO] ")
                (Progress::InProgress, "[IN PROGRESS] ")
                (Progress::Done, "[DONE] ")
                ;

        p_client = new Client(p_conn, p_cli);
        p_database = new MovieDatabase(p_client);
        p_client->registerObserver(this);
    };

    ~MediaHandler() {
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

    /*! \public startThreads
     * @brief starts threads from main.cpp
     */
    void startThreads() {
        std::promise<int> exit;
        std::future<int> futureObj = exit.get_future();

        std::promise<int> exit2;
        std::future<int> futureObj2 = exit2.get_future();

        std::thread thCli(&Client::handleCliThread, p_client, &exit2);

        std::thread thReq(&Client::handleRequestThread, p_client, &exit);

        auto result = futureObj2.get();
        if(result != 0) {
            m_logger->TRACE(Logger::ERR, "Client ended with error");
        }else {
            m_logger->TRACE(Logger::INFO, "Client ended normally");
        }
        thCli.join();

        auto status = futureObj.wait_for(std::chrono::microseconds(100));
        if(status != std::future_status::ready) {
            thReq.join();
        }
    }

private:

    /*! \var m_logger
     * @brief instance of @class StatusLogger
     */
    StatusLogger* m_logger;
    /*! \var p_conn
     * @brief instance of @class Connection
     */
    Connection *p_conn;
    /*! \var p_cli
     * @brief instance of @class Cli
     */
    Cli *p_cli;
    /*! \var p_database
     * @brief instance of @class MovieDatabase should be renamed to be more generic
     */
    Database *p_database;

    /*! \private getConnectionInfo
     * @brief calls @private updateDatabaseInfo and log status
     * @param event @enum Event used by @class Request
     * @param progress instance of @enum Progress used by @class Request
     */
    void getConnectionInfo();

};

#endif //MEDIAFW_MEDIAHANDLER_H
