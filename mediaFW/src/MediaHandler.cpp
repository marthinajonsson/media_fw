//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>


int MediaHandler::update(Request &request)
{
    Event event = request.getEvent();
    Progress progress = request.getProgress();

    getConnectionInfo(event, progress);

    if(event == Event::UPLOAD || event == Event::DELETE)  {
        if(progress == Progress::Done) {
            syncDatabase(request);
        }
    }
    else if (event == Event ::SEARCH) {
        status = Status::SEARCHING;
        if(progress == Progress::InProgress) {
            for (auto result : request.getMultipleResult()) {
                std::cout << "\nTITLE: " << result.second.at(0) << std::endl;
                std::cout << "GENRE: " << result.second.at(1) << std::endl;;
                std::cout << "DIRECTOR: " << result.second.at(2) << std::endl;;
                pop_front(result.second);
                pop_front(result.second);
                pop_front(result.second);
                for (const auto &s : result.second) {
                    std::cout << "ACTOR: " << s << std::endl;
                }
                std::cout << "\n\n";
            }
        }
        else if(progress == Progress::Done) {
            std::cout << "Search completed" << std::endl;
        }
    }

    return RET::OK;

}


void MediaHandler::getConnectionInfo(Event &event, Progress &progress) {

    bool connected = true ; //p_client->getConnectionStatus();

    if(connected) {
        m_logger->TRACE(Logger::INFO, "Server connection OK");

        if(progress == Progress::Done) {
            m_logger->TRACE(Logger::INFO, "Client is idle");
        }
        else if (progress == Progress::InProgress) {
            if(event == Event::UPLOAD) { m_logger->TRACE(Logger::INFO, "Client is uploading"); }
            else if(event == Event::DOWNLOAD) { m_logger->TRACE(Logger::INFO, "Client is downloading"); }
            else if(event == Event::SEARCH) {  m_logger->TRACE(Logger::INFO, "Client is searching"); }
            else if(event == Event::DELETE) {  m_logger->TRACE(Logger::INFO, "Client is purging"); }
            else if(event == Event::EXIT) { m_logger->TRACE(Logger::INFO, "Client is exiting"); }
        }
    }
    else {
        m_logger->TRACE(Logger::WARN, "Server disconnected");
    }

}


void MediaHandler::syncDatabase(const Request &request) {
    auto fut = std::async(updateDatabaseInfo, request);
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

MediaHandler::Status MediaHandler::updateDatabaseInfo(const Request &request)
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

