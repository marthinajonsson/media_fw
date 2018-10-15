//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"
#include "DatabaseItem.h"

/*! \class Client client.h "inc/client.h"
 *  \brief Class implementing the functionality of a client.
 *
 * Receives and interpretes information from stdin and sends requests to the server.
 */


void Client::setup()
{
    std::vector<std::string> resultVector;
    std::string choice;
    std::string exit = "exit";
    Connection *p_conn;
    std::future<std::vector<std::string>> fut;

    while(true)
    {
        resultVector.clear();
        //fut = std::async([&](auto *cli) -> std::vector<std::string> { return cli.daemon(); });
        fut = std::async(this->getCliInput, p_cli);
        auto result = fut.get();
        choice = result.front();
        std::cout << "Caught choice: " << choice << std::endl;
        if(choice.find(exit) != std::string::npos) {
            break;
        }

        handleCallback(result, p_conn->getConnectionStatus());
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

    Tags tag;
    tag.s_title = request.back();
    request.pop_back();

    tag.s_actors = {request.back()};
    request.pop_back();

    tag.s_director = request.back();
    request.pop_back();

    tag.s_genre = request.back();
    request.pop_back();

    DatabaseItem item;
    item.setFeature(tag);

    p_db->pushItem(item);
}