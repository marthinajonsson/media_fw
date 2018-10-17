//
// Created by mjonsson on 10/16/18.
//

#ifndef MEDIAFW_MEDIAHANDLER_H
#define MEDIAFW_MEDIAHANDLER_H

#include <Database/Database.h>
#include <Database/MovieDatabase.h>
#include "Cli.h"
#include "Client.h"
#include "StatusLogger.h"

class MediaHandler{
public:
    MediaHandler() {
        logger = new StatusLogger;
        cli = new Cli;
        client = new Client;
        database = new MovieDatabase;
        sync();
    };

    ~MediaHandler() {
        delete logger;
        delete cli;
        delete client;
        delete database;
    };

//    StatusLogger* getLoggerInstance() { this->logger; }

    void sync();
    void syncClient(std::string &status);
    void syncDatabase(std::string &status);


private:
    StatusLogger* logger;
    Client *client; // return error & status to user?
    Cli *cli;
    Database *database; // return info to user_

    static std::string getClientInfo(Client* p_client, const std::string & status) {
        return " ";// p_client->getUpdate();
    }

    static std::string getDatabaseInfo(Database* p_db, const std::string &status) {
        return " ";// p_client->getUpdate();
    }
};

#endif //MEDIAFW_MEDIAHANDLER_H
