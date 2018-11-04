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

    Client *p_client; // return error & status to user?

    MediaHandler () = default;

    MediaHandler(Category &category) : m_logger(new StatusLogger), p_cli(new Cli), p_conn(new Connection) {
        std::cout << "Mediahandler constructor" << std::endl;
        cat = category;
        p_client = new Client(p_conn, p_cli);

        if(category == Category::Series) {
            p_database = new SeriesDatabase;
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

    enum class Status { DOWNLOADING = 0, UPLOADING, STREAMING = 2, SEARCHING, DELETING, IDLE, DISCONNECT } status;

private:
    StatusLogger* m_logger;
    Connection *p_conn;
    Cli *p_cli;
    Database *p_database;
    Category cat;

    static Status getClientInfo(Client* p_client, const Status &status) { // TODO:these should be more clever
        return status;
    }

    static Status updateDatabaseInfo(const Request &request, const Status &status)
    {
        Category cat = request.getCategory();
        if(request.getEvent() == Event::UPLOAD ) {
            DatabaseItem item;
            item.setFeature(request);
            JsonParser::getInstance().add(cat, item);
            JsonParser::getInstance().load(cat);
            return Status::UPLOADING;
        }
        else if(request.getEvent() == Event::DELETE) {
            DatabaseItem item;
            item.setFeature(request);
            JsonParser::getInstance().remove(cat, item);
            JsonParser::getInstance().load(cat);
            return Status::DELETING;
        }
        return Status::IDLE;
    }
};

#endif //MEDIAFW_MEDIAHANDLER_H
