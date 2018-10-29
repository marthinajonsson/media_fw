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

std::mutex m;

/*! \class MediaHandler - handle for a user instance
 * @brief Synchronizes information from server and database,
 * Implements observer pattern.
 */

class MediaHandler : public Observer{
public:

    Client *p_client; // return error & status to user?

    MediaHandler(std::string category) : m_logger(new StatusLogger), p_cli(new Cli), p_conn(new Connection) {

        p_client = new Client(p_conn, p_cli);

        if(category.find("series")) {
            p_database = new MovieDatabase;
        }
        else {
            p_database = new MovieDatabase;
        }
        p_client->registerObserver(this);
        if(p_client->waitCliAsync() == 0) {

        }
    };

    ~MediaHandler() {
        p_client->removeObserver(this);
        delete m_logger;
        delete p_cli;
        delete p_client;
        delete p_database;
        std::cout << "Deconstructor MediaHandler" << std::endl;
    };



    bool update(Event event, std::vector<std::string>&) override;

    void syncClient(std::string &status);
    void syncDatabase(std::string &status, const std::vector<std::string>&);

    enum class Status { DOWNLOADING = 0, UPLOADING, STREAMING = 2, SEARCHING, IDLE, DISCONNECT } status;

private:
    StatusLogger* m_logger;
    Connection *p_conn;
    Cli *p_cli;
    Database *p_database;

    static std::string getClientInfo(Client* p_client, const std::string & status) {
        return status;
    }

    static std::string getDatabaseInfo(Database* p_db, const std::string &status) {
        return "OK";// p_client->getUpdate();
    }
};

#endif //MEDIAFW_MEDIAHANDLER_H
