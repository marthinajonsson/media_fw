//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"
#include "Util.h"

/*! \class Client client.h "inc/client.h"
 *  \brief Class implementing the functionality of a client.
 *
 * Receives and interpretes information from stdin and sends requests to the server.
 */

int Client::waitCliAsync()
{
    std::vector<std::string> resultVector;
    std::string choice;
    std::future<std::vector<std::string>> fut;
    while(true)
    {
        resultVector.clear();
        fut = std::async(getCliInput, p_cli);
        auto result = fut.get();
        choice = result.front();

        if(choice.find(EXIT) != std::string::npos) {
            break;
        }

        handleRequest(result);
    }
    if(choice.find(EXIT) != std::string::npos) {
        return RET::OK;
    }
    return RET::ERROR;
}

void Client::notifyRequest(std::vector<std::string> &request) {

    if (request.front() == UPLOAD) {
        notifyObservers(Event::UPLOAD, request);
    }
    else if (request.front() == DOWNLOAD) {
        notifyObservers(Event::DOWNLOAD, request);
    }
    else if (request.front() == SEARCH) {
        notifyObservers(Event::SEARCH, request);
    }
    else if (request.front() == DELETE) {
        notifyObservers(Event::DELETE, request);
    }
    else if (request.front().find(EXIT) != std::string::npos) {
        notifyObservers(Event::EXIT, request);
    }
    else {
        m_logger->TRACE(Logger::ERR, "Unknown request");
    }
}

void Client::handleRequest(std::vector<std::string> &request)
{
    notifyRequest(request);
    std::string result;
    std::string testcommand = "ls";
    p_conn->sendServerRequest(testcommand, result);
    std::cout << result << std::endl;
}
