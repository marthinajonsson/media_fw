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

//TODO: how should info from getCliInput reach mediaHandler?
void Client::setup()
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
        std::cout << "Caught choice: " << choice << std::endl;
        if(choice.find(exit) != std::string::npos) {
            break;
        }

        handleCallback(result, connected);
    }
}

void Client::handleCallback(std::vector<std::string> request, bool connected)
{
    std::string choice = request.front();
    std::string command;
    if (choice == "upload") {
        command = "ls";
    }else if (choice == "download") {
        command = "ps aux";
    }
    else if (choice == "search") {
        command = "ifconfig";
    }else {
        std::cerr << "Unknown request" << std::endl;
    }

    std::string result {""};
    if(connected == false) {
        p_conn->sendRemoteCommands(command, result);
    }
    std::cout << "Request sent: " << command << std::endl;
}

bool Client::getConnectionStatus() {
    return p_conn->getConnectionStatus();
}