//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>


int MediaHandler::update(Request &request)
{
    Event event = request.getEvent();

    syncClient();

    if(event == Event::UPLOAD) {
        status = Status::UPLOADING;
        syncDatabase(request);
    }
    else if (event == Event ::DOWNLOAD) {
        status = Status::DOWNLOADING;
    }
    else if (event == Event ::SEARCH) {
        status = Status::SEARCHING;
        for(auto result : request.getMultipleResult()) {
            std::cout << "TITLE: " << result.second.at(0) << std::endl;
            std::cout << "GENRE: " << result.second.at(1) << std::endl;;
            std::cout << "DIRECTOR: " << result.second.at(2) << std::endl;;
            pop_front(result.second);
            pop_front(result.second);
            pop_front(result.second);
            for(const auto &s : result.second) {
                std::cout << "ACTOR: " << s << std::endl;
            }
            std::cout << "\n\n";
        }
    }
    else if (event == Event::DELETE) {
        status = Status::DELETING;
        syncDatabase(request);
    }
    else if (event == Event ::HELP) {
        status = Status::IDLE;
    }
    else if (event == Event ::EXIT) {
        status = Status::DISCONNECT;
    }
    else {
        return RET::ERROR;
    }

    return RET::OK;

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

void MediaHandler::syncDatabase(const Request &request) {
    //TODO: connect more status reports
    auto fut = std::async(updateDatabaseInfo, request, status);
    auto answer = fut.get();
    if(answer == Status::IDLE) {
        m_logger->TRACE(Logger::INFO, "Database is synced");
    }else {
        m_logger->TRACE(Logger::WARN, "Database is unsynced");
    }

    if(answer == Status::UPLOADING) {
        m_logger->TRACE(Logger::INFO, "Uploading.. ");
    }
    else if (answer == Status::DELETING) {
        m_logger->TRACE(Logger::INFO, "Deleting.. ");
    }

}

