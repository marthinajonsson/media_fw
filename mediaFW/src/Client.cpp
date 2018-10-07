//
// Created by mjonsson on 10/4/18.
//
#include <future>

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

void Client::setup()
{
    Connection conn;
    Cli cli;
}

void Client::handleCliCallback(std::string request) {

    //std::string request {""};

    Tags tag;
    tag.s_actors = {"Matt Damon, Julia Roberts"};
    tag.s_director = "Marthina";
    tag.s_genre = "Thriller";
    tag.s_title = "In the dark";
    DatabaseItem item;
    item.setFeature(tag);

    std::string test = item.getTitle();
    if(test == tag.s_title){
        std::cout << "title worked" << std::endl;
    }
    db->pushItem(item);

    if(request == "print processes") {
        conn->sendRemoteCommands(request);
    }
}