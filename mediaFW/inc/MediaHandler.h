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
        p_database_movie = new MovieDatabase;
        p_database_series = new SeriesDatabase;
        p_client->registerObserver(this);
    };

    ~MediaHandler() {
        p_client->removeObserver(this);
        delete m_logger;
        delete p_cli;
        delete p_client;
        delete p_database_movie;
        delete p_database_series;
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
    /*! \var p_database_movie
     * @brief instance of @class MovieDatabase should be renamed to be more generic
     */
    Database *p_database_movie;
    Database *p_database_series;

    /*! \enum Status
     * @brief describing current progress state
     * @var DOWNLOADING
     * @var UPLOADING
     * @var STREAMING
     * @var SEARCHING
     * @var DELETEING
     * @var IDLE
     * @var DISCONNECT
     */
    enum class Status { DOWNLOADING = 0, UPLOADING, STREAMING = 2, SEARCHING, DELETING, IDLE, DISCONNECT } status;

    /*! \private syncDatabase
     * @brief check server connection status with @var p_client and log status
     * @param request incoming from threads
     */
    void syncDatabase(const Request &request);
    /*! \private getConnectionInfo
     * @brief calls @private updateDatabaseInfo and log status
     * @param event @enum Event used by @class Request
     * @param progress instance of @enum Progress used by @class Request
     */
    void getConnectionInfo(Event &event, Progress &progress);
    /*! \private updateDatabaseInfo
     * @brief updates db.json after request
     * @param request instance of @class Request
     * @return @enum Status
     */
    static Status updateDatabaseInfo(const Request &request);
};

#endif //MEDIAFW_MEDIAHANDLER_H
