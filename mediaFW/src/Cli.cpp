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


std::vector<std::string> Cli::daemon() {
    const std::string exit = "exit";
    const std::string help = "help";
    std::string p_choice;

    printOptions();
#ifndef UNIT_TEST

    for (std::string line; std::cout << "APP > " && std::getline(std::cin, line); )
    {
        if (line == help) {
            printOptions();
        }
        else if (!line.empty()) {
            return parseArg(line);
        }
    }

#endif
}

std::vector<std::string> Cli::parseArg(std::string &input) {
    std::stringstream m_stream(input);
    std::vector<std::string> seglist;
    std::string segment;
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
    std::cout << "\n" << std::endl;
    std::string header {"<choice> <optional arg1>.. <optimal arg2>.."};
    std::string choice {"<choice> = upload, download, search, exit"};
    std::string opt {"<arg> = title, genre, director, list of actors"};
    std::cout << header << "\n" << choice << "\n" << opt << "\n" << "\n" << std::endl;
}
