//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"
#include "Cli.h"
#include "DatabaseItem.h"
#include "Connection.h"


/// <summary>
/// A method that waits for CLI to process incoming request.
/// Used by std::future.
/// </summary>
/// <param name="p_cli">A pointer to current CLI object.</param>
/// <returns>A vector of strings containing the result of CLI process</returns>
std::vector<std::string> getCliInput(Cli* p_cli) {
    return p_cli->process();
}

/// <summary>
/// A method that waits CLI input from method getCliInput.
/// The method will break if input is interpreted as exit or
/// continue by sending the request to be handled.
/// </summary>
/// <returns></returns>
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
        fut = std::async(getCliInput, p_cli);
        auto result = fut.get();
        choice = result.front();
        std::cout << "Caught choice: " << choice << std::endl;
        if(choice.find(exit) != std::string::npos) {
            break;
        }

        handleCliCallback(result, p_conn->getConnectionStatus());
    }
}


/// <summary>
/// This method performs what is requested by CLI.
/// Both remotely and on local database.
/// </summary>
/// <param name="request">A string containing a request (e.g. upload, search)
/// and also additional information needed to handle the request such as title.</param>
/// <param name="connected">Boolean parameter indicating wheater or not we are able to
/// send request remotely (i.e. established ssh connection).</param>
/// <returns></returns>
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