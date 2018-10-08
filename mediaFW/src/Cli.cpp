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


std::vector<std::string> Cli::handleInput(std::string input, std::vector<std::string> &args) {

    args = parseArg(input);
    std::cout << "Choice by cli " << args.front() << std::endl;
    return args;
}

std::vector<std::string> Cli::daemon() {
    printOptions();
    std::string p_choice;
    std::vector<std::string> m_args;
    m_args.clear();
    m_args.reserve(10);

    const std::string quit = "q";
    const std::string help = "help";

    for (std::string line; std::cout << "APP > " && std::getline(std::cin, line); )
    {
        if(line == quit){
            std::cout<<"Bye bye" <<std::endl;
            break;
        }
        else if (line == help) {
            printOptions();
        }
        else if (!line.empty()) {
            return handleInput(line, m_args);
        }
    }
    // push to notify result from this to client
}

std::vector<std::string> Cli::parseArg(std::string &input) {
    std::stringstream m_stream(input);
    std::string segment;
    std::vector<std::string> seglist;
    seglist.reserve(15);
    seglist.clear();

    while(std::getline(m_stream, segment, ' '))
    {
        seglist.push_back(segment);
    }
    std::cout << "Number of arguments: " << seglist.size() << std::endl;
    return seglist;
}

void Cli::printOptions() {

    std::string header {"<choice> <optional arg1>.. <optimal arg2>.."};
    std::string choice {"<choice> = upload, download, search"};
    std::string opt {"<arg> = title, genre, director, list of actors"};
    std::cout << header << "\n" << choice << "\n" << opt << "\n" << "\n" << std::endl;
}
