//
// Created by mjonsson on 9/30/18.
//


#include <iostream>
#include <sstream>
#include "Cli.h"


/*! \class Cli cli.h "inc/cli.h"
 *  \brief Class implementing the functionality of a command line interface.
 *
 * Receives inputs from STDIN and splits the result into strings.
 */


std::vector<std::string> Cli::process() {
    const std::string help = "help";
    std::string p_choice;

    printOptions();
    for (std::string line; std::cout << "APP > " && std::getline(std::cin, line); )
    {
        if (line == help) {
            printOptions();
        }
        else if (!line.empty()) {
            return parseArg(line);
        }
    }
}

/*! \private Cli::parseArg(std::string &input)
     * @brief Test Parses argv and splits into strings.
     * @param input A long input string containing argv from stdin.
     * @return Private vector of strings containing parsed words from stdin.
     */
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
    return seglist;
}

/*! \private Cli::printOptions()
 * @brief Test A private method that prints all valid options for stdin.
 */
void Cli::printOptions() {
    std::cout << "\n" << std::endl;
    std::string header {"<choice> <optional arg1>.. <optimal arg2>.."};
    std::string choice {"<choice> = upload, download, search, delete, exit"};
    std::string opt {"<arg> = title, genre, director, list of actors"};
    std::cout << header << "\n" << choice << "\n" << opt << "\n" << "\n" << std::endl;
}
