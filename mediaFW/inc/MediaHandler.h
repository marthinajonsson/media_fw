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


class MediaHandler : public Observer{
public:
    MediaHandler() {
        Connection *conn;
        logger = new StatusLogger;
        cli = new Cli;

        client = new Client(conn, cli);
        database = new MovieDatabase;

        std::string status;
        client->registerObserver(this);
        client->waitCliAsync();
    };

    ~MediaHandler() {
        delete logger;
        delete cli;
        delete client;
        delete database;
    };

//    StatusLogger* getLoggerInstance() { this->logger; }


    void update(Event event, std::vector<std::string>&) override;

    void syncClient(std::string &status);
    void syncDatabase(std::string &status, const std::vector<std::string>&);


private:
    StatusLogger* logger;
    Client *client; // return error & status to user?
    Cli *cli;
    Database *database; // return info to user_

    static std::string getClientInfo(Client* p_client, const std::string & status) {
        return "OK";// p_client->getUpdate();
    }

    static std::string getDatabaseInfo(Database* p_db, const std::string &status) {
        return "OK";// p_client->getUpdate();
    }
};

#endif //MEDIAFW_MEDIAHANDLER_H
