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

    Client *p_client; // return error & status to user?

    MediaHandler () = default;

    MediaHandler(std::string category) : m_logger(new StatusLogger), p_cli(new Cli), p_conn(new Connection) {
        std::cout << "Mediahandler constructor" << std::endl;
        p_client = new Client(p_conn, p_cli);

        if(category.find("series")) {
            p_database = new MovieDatabase;
        }
        else {
            p_database = new MovieDatabase;
        }
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


    void startCliThread() {
        int result = p_client->waitCliAsync(); // will return when "exit" has been requested and block until then.
        if(result != 0) {
            m_logger->TRACE(Logger::ERR, "Client ended with error");
        }else {
            m_logger->TRACE(Logger::INFO, "Client ended normally");
        }
    }

    int update(Request &) override;  // this should only report status from observation, cli thread should run and stop itself.

    void syncClient();
    void syncDatabase(const Request &request);

    enum class Status { DOWNLOADING = 0, UPLOADING, STREAMING = 2, SEARCHING, IDLE, DISCONNECT } status;

private:
    StatusLogger* m_logger;
    Connection *p_conn;
    Cli *p_cli;
    Database *p_database;

    static Status getClientInfo(Client* p_client, const Status &status) { // TODO:these should be more clever
        return status;
    }

    static Status getDatabaseInfo(Database* p_db, const Status &status) {
        return Status::IDLE;
    }
};

#endif //MEDIAFW_MEDIAHANDLER_H
