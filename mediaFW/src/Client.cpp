//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"

/*! \class Client client.h "inc/client.h"
 *  \brief Class implementing the functionality of a client.
 *
 * Receives and interpretes information from stdin and sends requests to the server.
 */

void Client::waitCliAsync()
{
    std::vector<std::string> resultVector;
    std::string choice;
    std::string exit = "exit";
    std::future<std::vector<std::string>> fut;
    bool connected = p_conn->getConnectionStatus();
    while(true)
    {
        resultVector.clear();
        //fut = std::async([&](auto *cli) -> std::vector<std::string> { return cli.daemon(); });
        fut = std::async(getCliInput, p_cli);
        auto result = fut.get();
        choice = result.front();

        if(choice.find(exit) != std::string::npos) {
            break;
        }

        handleRequest(result, connected);
    }
}

void Client::notifyRequest(std::vector<std::string> &request) {

    if (request.front() == "upload") {
        notifyObservers(Event::UPLOAD, request);
    }else if (request.front() == "download") {
        notifyObservers(Event::DOWNLOAD, request);
    }
    else if (request.front() == "search") {
        notifyObservers(Event::SEARCH, request);
    }
    else if (request.front() == "delete") {
        notifyObservers(Event::DELETE, request);
    }
    else if (request.front().find("exit")) {
        notifyObservers(Event::EXIT, request);
    }
    else {
        std::cerr << "Unknown request" << std::endl;
    }
}

void Client::handleRequest(std::vector<std::string> request, bool connected)
{
    notifyRequest(request);

    std::string result;
    if(connected == true) {
        p_conn->sendRemoteCommands("ls", result);
    }
}
