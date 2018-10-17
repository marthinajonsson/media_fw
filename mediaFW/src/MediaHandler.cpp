//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>

bool timer() {
    std::this_thread::sleep_for(std::chrono::seconds(30));
    return true;
}


void MediaHandler::sync()
{
    std::string result;
    while(true)
    {
        auto future = std::async(timer);
        future.get();
        syncClient(result);

        if(result == "exit") {
            break;
        }
        syncDatabase(result);
    }
}

void MediaHandler::syncClient(std::string &status) {

    bool connected = client->getConnectionStatus();
    status = "NOK";

    if(connected) {
        auto level = logger->getEnum("OK");
        logger->TRACE(level, "Server connection OK");

        auto fut = std::async(getClientInfo,client, status);
        auto answer = fut.get();
        if(answer == "OK") {
            level = logger->getEnum("OK");
            logger->TRACE(level, "Client sync OK");
            status = "OK";
        }
        else if (answer == "exit"){
            status = answer;
        }
        else {
            level = logger->getEnum("NOK");
            logger->TRACE(level, "Client sync NOK");
        }
    }
    else {
        auto level = logger->getEnum("NOK");
        logger->TRACE(level, "Server disconnected");
    }

}

void MediaHandler::syncDatabase(std::string &status) {
    //TODO: get db status
    //TODO: update db with new info
    auto fut = std::async(getDatabaseInfo, database, status);
    auto answer = fut.get();
    if(answer == "OK") {
        auto level = logger->getEnum("OK");
        logger->TRACE(level, "Database is synced");
    }else {
        auto level = logger->getEnum("NOK");
        logger->TRACE(level, "Database is unsynced");
    }
}
