//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>


void MediaHandler::update(Event event, std::vector<std::string> &args)
{
    std::string result;

    if(event == Event::UPLOAD) {
        result = "Upload";
    }
    else if (event == Event ::DOWNLOAD) {
        result = "Download";
    }
    else if (event == Event ::SEARCH) {
        result = "Search";
    }
    else if (event == Event ::HELP) {
        result = "Help";
    }
    else if (event == Event ::EXIT) {
        result = "Exit";
    }

    std::cout << result << std::endl;

    syncClient(result);
    syncDatabase(result, args);
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

void MediaHandler::syncDatabase(std::string &status, const std::vector<std::string> &args) {
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
