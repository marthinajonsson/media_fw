//
// Created by mjonsson on 9/30/18.
//


#include <iostream>
#include <sstream>
#include <unistd.h>

#include "Cli.h"
#include <JsonParser.h>

/*! \class Cli cli.h "inc/cli.h"
 *  \brief Class implementing the functionality of a command line interface.
 *
 * Receives inputs from STDIN and splits the result into strings.
 */

std::vector<std::string> Cli::process()
{
    std::vector<std::string> parsed;
    printOptions();

    for (std::string line; std::cout << "MEDIAFW > " && std::getline(std::cin, line); )
    {
        if (line.find("help") != 0) {
            printOptions();
        }
        else if (line.find("exit")) {
            return {"exit"};
        }
        else if (!line.empty()) {
            parsed = parseArg(line);
            if(!verifyParsed(parsed)) {
                return {""};
            }
            return parsed;
        }
    }
}

std::vector<std::string> Cli::process(std::string &testinput)
{
    std::vector<std::string> parsed;
    if(testinput.find("help")){
        printOptions();
    }

    if (!testinput.empty()) {
        parsed = parseArg(testinput);
        if(!verifyParsed(parsed)) {
            return {""};
        }
        return parsed;
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

    while(std::getline(m_stream, segment, ':'))
    {
        seglist.push_back(segment);
    }
    return seglist;
}

bool Cli::verifyParsed(std::vector<std::string> &parsed) {
    auto choice = parsed.front();

    if(choice == "upload") {
        if (verifyUpload(parsed)) {
            if(cfmUpload(parsed)) {
                return true;
            }
        }
    }
    else if (choice == "download") {
        if(verifyDownload(parsed)) {
            return true;
        }
    }
    else if (choice == "search") {
        if(verifySearch(parsed)) {
            return true;
        }
    }
    else if (choice == "delete") {
        if(verifyDelete(parsed)) {
            return true;
        }
    }
    return false;
}

bool Cli::verifyExists(const std::string &s) {
    bool result = JsonParser::getInstance().find(MOVIE, s);
    return result;
}

bool Cli::verifyDelete(std::vector<std::string> &parsed) {
    const auto title = parsed.back();
    if (title.empty()) { return false; }

    return verifyExists(title);
}

bool Cli::verifySearch(std::vector<std::string> &parsed) {

    const auto title = parsed.back();
    if (title.empty()) { return false; }

    return verifyExists(title);
}

bool Cli::verifyDownload(std::vector<std::string> &parsed) {

    const auto title = parsed.at(1);
    if (title.empty()) { return false; }

    return verifyExists(title);
}

bool Cli::verifyUpload(std::vector<std::string> &parsed) {

    const auto filename = parsed.back();
    if (filename.empty()) { return false; }

    return ( access( filename.c_str(), F_OK ) != -1 );
}

bool Cli::cfmUpload(std::vector<std::string> &uploadstr) {

    std::cout << "To confirm your upload add the following info: \n"
                 "\t <title> <genre> <director> {<actor> <actor>.. }" << std::endl;

    std::string info;
    std::string answer;

    std::getline(std::cin, info);
    auto parsed = parseArg(info);
    std::cout << "Please confirm <title> " << parsed.front() <<
    "\n <genre> " << parsed.at(1) << " <director> " << parsed.at(2) << " and the following actors: \n" << std::endl;

    for (auto it = uploadstr.begin() + 2; it != uploadstr.end(); ++it){
        std::cout << *it << std::endl;
    }

    std::cout << "Y or n? ";
    std::getline(std::cin, answer);
    return answer.find('n') == 0;
}


/*! \private Cli::printOptions()
 * @brief Test A private method that prints all valid options for stdin.
 */
void Cli::printOptions() {
    std::cout << "\n" << std::endl;

    auto choice {"<choice> = upload, download, search, delete\n"};

    auto upload = "<upload> <filename> \n\t*<filename> - absolute path to filename. \n";
    auto cmfupload = "\t To confirm your upload add the following info: \n\t <title> <genre> {<actor> <actor>.. } <director>\n\n";

    auto download = "<download> <movie/series> <title> \n";
    auto cfmdownload = "\t Title exists or did you mean 'abc'? \n\t Download completed\n\n";

    auto search {"<search> <args>.. \n \t <args>: title, genre, director, list of actors\n"};
    auto cfmsearch = "\t Found the following matches..\n\n";

    auto deleted {"<delete> <title>\n"};
    auto cfmdelete = "\t Sure you want to delete, Y or n? \n\n";

    auto disconnect = "Write 'exit' to disconnect\n";

    std::cout << choice << "\nExample input..\n\n" << upload << cmfupload << download << cfmdownload << search
    << cfmsearch << deleted << cfmdelete << std::endl;
    std::cout << disconnect << std::endl;
}
