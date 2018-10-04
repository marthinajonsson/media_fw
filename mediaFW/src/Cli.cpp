//
// Created by mjonsson on 9/30/18.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Cli.h"


void Cli::handleInput(std::string input) {
    std::string original (input);
    CHOICE ch;
    ch = NO_OPTION;

    std::vector<std::string> _args = parseArg(input);
    if("help" == _args.front() || "-h") {
        printOptions();
    }

    std::string choice = _args.front();
    if( choice == "upload") {
        ch = UPLOAD;
        std::cout << "you have chosen to upload" << std::endl;
    }
    else if (choice == "download") {
        ch = DOWNLOAD;
        std::cout << "you have chosen to download" << std::endl;
    }
    else if (choice == "search") {
        ch = SEARCH;
        std::cout << "you have chosen to search" << std::endl;
    }
    else{
        std::cout << "this choice is not recognizable" << std::endl;
    }


    for(std::string arg : _args) {
        if(ch == SEARCH) {

        }else if (ch == UPLOAD || ch == DOWNLOAD) {

        }
    }
}

void Cli::daemon() {
    std::cout<<"cli daemon started" <<std::endl;
    std::string quit = "q";

    for (std::string line; std::cout << "APP > " && std::getline(std::cin, line); )
    {

        if(line == quit){
            std::cout<<"cli daemon stopped" <<std::endl;
            break;
        }
        else if (!line.empty()) {
            handleInput(line);
        }
    }
}

std::vector<std::string> Cli::parseArg(std::string &input) {
    std::stringstream test(input);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(test, segment, ' '))
    {
        seglist.push_back(segment);
    }
}

void Cli::printOptions() {

    std::string header {"<choice> <optional arg1>.. <optimal arg2>.."};
    std::string choice {"upload, download, search"};
    std::string opt {"title, genre, director, list of actors"};
}
