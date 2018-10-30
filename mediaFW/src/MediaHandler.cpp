//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>


bool MediaHandler::update(Event &event, std::vector<std::string> &args)
{
    if(event == Event::UPLOAD) {
        status = Status::UPLOADING;
    }
    else if (event == Event ::DOWNLOAD) {
        status = Status::DOWNLOADING;
    }
    else if (event == Event ::SEARCH) {
        status = Status::SEARCHING;
    }
    else if (event == Event ::HELP) {
        status = Status::IDLE;
    }
    else if (event == Event ::EXIT) {
        status = Status::DISCONNECT;
    }
    else {
        return false;
    }
    return true;
    syncClient();
    syncDatabase(args);

}

void MediaHandler::syncClient() {

    bool connected = p_client->getConnectionStatus();

    if(connected) {
        auto level = m_logger->getEnum("OK");
        m_logger->TRACE(level, "Server connection OK");

        auto fut = std::async(getClientInfo, p_client, status);
        auto answer = fut.get();

        if(Status::IDLE == answer) {
            m_logger->TRACE(level, "Client is idle");
        }
        else if(Status::SEARCHING == answer){
            m_logger->TRACE(level, "Client is searching");
        }
        else if(Status::DOWNLOADING == answer){
            m_logger->TRACE(level, "Client is downloading");
        }
        else if(Status::UPLOADING == answer){
            m_logger->TRACE(level, "Client is uploading");
        }
        else if(Status::STREAMING == answer){
            m_logger->TRACE(level, "Client is streaming");
        }
        else if(Status::DISCONNECT == answer){
            m_logger->TRACE(level, "Client is disconnected");
        }
    }
    else {
        auto level = m_logger->getEnum("NOK");
        m_logger->TRACE(level, "Server disconnected");
    }

}

void MediaHandler::syncDatabase(const std::vector<std::string> &args) {
    //TODO: get db status
    //TODO: update db with new info
    auto fut = std::async(getDatabaseInfo, p_database, status);
    auto answer = fut.get();
    if(answer == Status::IDLE) {
        auto level = m_logger->getEnum("OK");
        m_logger->TRACE(level, "Database is synced");
    }else {
        auto level = m_logger->getEnum("NOK");
        m_logger->TRACE(level, "Database is unsynced");
    }
}

