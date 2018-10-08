//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"
#include "Cli.h"
#include "DatabaseItem.h"
#include "Connection.h"


void Client::initiateDatabase(DbType type) {

    if(type = Movie){
       db  = new MovieDatabase;
    }
    else {
        //Database *db = new SeriesDatabase;
    }
}

const DbType Client::getCurrentDbType() {
    return this->type;
}

void Client::setup()
{
    std::vector<std::string> resultVector;
    resultVector.reserve(10);
    resultVector.clear();
    std::string choice;
    Connection conn;

    std::cout << "Welcome to client setup" << std::endl;

    auto popper = std::async(std::launch::async, [&resultVector]() -> std::vector<std::string> {
        Cli cli;
        return cli.daemon();
    });

    auto result = popper.get();
    for(std::string s : result){
        std::cout << "Caught choice: " << s << std::endl;
    }

    handleCliCallback(result, conn.getConnectionStatus());

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


    std::string result {""};
    if(connected) {
        conn->sendRemoteCommands(command, result);
    }

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