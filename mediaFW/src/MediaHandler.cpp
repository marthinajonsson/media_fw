//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>


bool MediaHandler::update(Event event, std::vector<std::string> &args)
{
    std::string result;

    if(event == Event::UPLOAD) {
        result = "Upload";
        status = Status::UPLOADING;
    }
    else if (event == Event ::DOWNLOAD) {
        result = "Download";
        status = Status::DOWNLOADING;
    }
    else if (event == Event ::SEARCH) {
        result = "Search";
        status = Status::SEARCHING;
    }
    else if (event == Event ::HELP) {
        result = "Help";
        status = Status::IDLE;
    }
    else if (event == Event ::EXIT) {
        auto level = m_logger->getEnum("OK");
        m_logger->TRACE(level, "Exit..");
        status = Status::DISCONNECT;
        return true;
    }
    else {
        return false;
    }

    std::cout << result << std::endl;

    syncClient(result);
    syncDatabase(result, args);
    return true;
}

void MediaHandler::syncClient(std::string &status) {

    bool connected = p_client->getConnectionStatus();
    status = "NOK";

    if(connected) {
        auto level = m_logger->getEnum("OK");
        m_logger->TRACE(level, "Server connection OK");

        auto fut = std::async(getClientInfo, p_client, status);
        auto answer = fut.get();
        if(answer == dsdsd) {
            level = m_logger->getEnum("OK");
            m_logger->TRACE(level, "Client sync OK");
            status = "OK";
        }
        else if (answer == "exit"){
            status = answer;
        }
        else {
            level = m_logger->getEnum("NOK");
            m_logger->TRACE(level, "Client sync NOK");
        }
    }
    else {
        auto level = m_logger->getEnum("NOK");
        m_logger->TRACE(level, "Server disconnected");
    }

}

void MediaHandler::syncDatabase(std::string &status, const std::vector<std::string> &args) {
    //TODO: get db status
    //TODO: update db with new info
    auto fut = std::async(getDatabaseInfo, p_database, status);
    auto answer = fut.get();
    if(answer == "OK") {
        auto level = m_logger->getEnum("OK");
        m_logger->TRACE(level, "Database is synced");
    }else {
        auto level = m_logger->getEnum("NOK");
        m_logger->TRACE(level, "Database is unsynced");
    }
}

