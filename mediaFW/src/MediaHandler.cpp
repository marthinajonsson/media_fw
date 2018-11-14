//
// Created by mjonsson on 10/16/18.
//


#include "MediaHandler.h"
#include <future>
#include <thread>


int MediaHandler::update(Request &request)
{
    getConnectionInfo();

    Event event = request.getEvent();
    Progress progress = request.getProgress();

    auto e = m_eventMap.at(event);
    auto p = m_progressMap.at(progress);
    std::string t = "Request ";
    std::string str = t + e + p;

    std::cout << str << std::endl;

    if(request.getError() == RET::ERROR) {
        m_logger->TRACE(Logger::ERR, str, request.getErrorDesc());
    }else {
        m_logger->TRACE(Logger::INFO, str);
    }

    if (event == Event ::SEARCH && progress == Progress::Done) {

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
    return RET::OK;
}


void MediaHandler::getConnectionInfo() {

    bool connected = true ; //p_client->getConnectionStatus();

    if(connected) {
        m_logger->TRACE(Logger::INFO, "Server connection OK");
    }
    else {
        m_logger->TRACE(Logger::WARN, "Server disconnected");
    }

}



