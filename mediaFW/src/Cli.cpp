//
// Created by mjonsson on 9/30/18.
//

/*
 * This module should only wait and process keyboard input
 * */

#include <iostream>
#include <vector>
#include <sstream>
#include "Cli.h"


std::vector<std::string> Cli::handleInput(std::string input, std::string &choice, std::vector<std::string> &args) {
    std::string original (input);
    CHOICE ch;
    ch = NO_OPTION;

    args = parseArg(input);

    std::cout << args.size() << std::endl;

    if("help" == args.front() || "-h") {
        printOptions();
    }

    std::cout << args.front() << std::endl;

    return args;
}

std::vector<std::string> Cli::daemon(std::string &choice) {
    std::cout<<"cli daemon started" <<std::endl;
    //std::string choice;
    std::vector<std::string> args;

    const std::string quit = "q";

    for (std::string line; std::cout << "APP > " && std::getline(std::cin, line); )
    {
        if(line == quit){
            std::cout<<"cli daemon stopped" <<std::endl;
            break;
        }
        else if (!line.empty()) {
            return handleInput(line, choice, args);
        }
    }
    // push to notify result from this to client
}

std::vector<std::string> Cli::parseArg(std::string &input) {
    std::stringstream test(input);
    std::string segment;
    std::vector<std::string> seglist{};

    seglist.push_back("upload");

    while(std::getline(test, segment, ' '))
    {
        seglist.push_back(segment);
    }
}

void Cli::printOptions() {

    std::string header {"<choice> <optional arg1>.. <optimal arg2>.."};
    std::string choice {"<choice> = upload, download, search"};
    std::string opt {"<arg> = title, genre, director, list of actors"};
    std::cout << header << "\n" << choice << "\n" << opt << std::endl;
}
