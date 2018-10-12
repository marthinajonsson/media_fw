//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"
#include "Cli.h"
#include "DatabaseItem.h"
#include "Connection.h"

std::vector<std::string> getCliInput(Cli* p_cli) {
    return p_cli->daemon();
}


void Client::setup()
{
    std::vector<std::string> resultVector;
    std::string choice;
    std::string exit = "exit";
    Connection *p_conn;
    std::cout << "Welcome to client setup" << std::endl;
    std::future<std::vector<std::string>> fut;

    while(true)
    {
        resultVector.clear();
        //fut = std::async([&](auto *cli) -> std::vector<std::string> { return cli.daemon(); });
        fut = std::async(getCliInput, p_cli);
        auto result = fut.get();
        choice = result.front();
        std::cout << "Caught choice: " << choice << std::endl;
        if(choice.find(exit) != std::string::npos) {
            std::cout << "Caught exit: " << choice << std::endl;
            break;
        }

        handleCliCallback(result, p_conn->getConnectionStatus());
    }
}

void Client::handleCliCallback(std::vector<std::string> request, bool connected)
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

#ifndef UNIT_TEST
    std::string result {""};
    if(connected == false) {
        p_conn->sendRemoteCommands(command, result);
    }
#endif
    std::cout << "Request sent: " << command << std::endl;
//
//    Tags tag;
//    tag.s_title = request.back();
//    request.pop_back();
//
//    tag.s_actors = {request.back()};
//    request.pop_back();
//
//    tag.s_director = request.back();
//    request.pop_back();
//
//    tag.s_genre = request.back();
//    request.pop_back();
//
//    DatabaseItem item;
//    item.setFeature(tag);
//
//    db->pushItem(item);
}