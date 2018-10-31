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

    syncClient();
    syncDatabase(args);
    return true;

}

void MediaHandler::syncClient() {

    bool connected = true ; //p_client->getConnectionStatus();

    if(connected) {
        m_logger->TRACE(Logger::INFO, "Server connection OK");

        auto fut = std::async(getClientInfo, p_client, status);
        auto answer = fut.get();

        if(Status::IDLE == answer) {
            m_logger->TRACE(Logger::INFO, "Client is idle");
        }
        else if(Status::SEARCHING == answer){
            m_logger->TRACE(Logger::INFO, "Client is searching");
        }
        else if(Status::DOWNLOADING == answer){
            m_logger->TRACE(Logger::INFO, "Client is downloading");
        }
        else if(Status::UPLOADING == answer){
            m_logger->TRACE(Logger::INFO, "Client is uploading");
        }
        else if(Status::STREAMING == answer){
            m_logger->TRACE(Logger::INFO, "Client is streaming");
        }
        else if(Status::DISCONNECT == answer){
            m_logger->TRACE(Logger::INFO, "Client is disconnected");
        }
    }
    else {
        m_logger->TRACE(Logger::WARN, "Server disconnected");
    }

}

void MediaHandler::syncDatabase(const std::vector<std::string> &args) {
    //TODO: get db status
    //TODO: update db with new info
    auto fut = std::async(getDatabaseInfo, p_database, status);
    auto answer = fut.get();
    if(answer == Status::IDLE) {
        m_logger->TRACE(Logger::INFO, "Database is synced");
    }else {
        m_logger->TRACE(Logger::WARN, "Database is unsynced");
    }
}

