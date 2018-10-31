//
// Created by mjonsson on 9/30/18.
//


#include <iostream>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <iterator>

#include "Cli.h"
#include <JsonParser.h>

/*! \class Cli cli.h "inc/cli.h"
 *  \brief Class implementing the functionality of a command line interface.
 *
 * Receives inputs from STDIN and splits the result into strings.
 */

Request Cli::process()
{
    std::vector<std::string> parsed;
    Event event;
    for (std::string line; std::cout << "MEDIAFW > " && std::getline(std::cin, line); )
    {
        if (line.find(HELP) != std::string::npos) {
            printOptions();
        }
        else if (line.find(EXIT) != std::string::npos) {
            return Request(Event::EXIT);
        }
        else if (!line.empty()) {
            parsed = parseArg(line, ':');
            checkValid(parsed.front(), event);
            // TODO: strip away choice from parsed and use event only
            Request req (event);
            if(!verifyParsed(parsed, req, false)) {
                return req;
            }
            return parsed;
        }
    }
}

std::vector<std::string> Cli::process(std::string &testinput)
{
    std::vector<std::string> parsed;
    Event event;
    if(testinput.find(HELP) != std::string::npos){
        printOptions();
    }

    if (!testinput.empty()) {
        parsed = parseArg(testinput, ':');
        if(!verifyParsed(parsed, event, true)) {
            return {""};
        }
        return parsed;
    }
}

int Cli::checkValid(const std::string &choice, Event &event){
    auto result = RET::ERROR;
    auto it = std::find(VALID.begin(), VALID.end(), choice);
    if(it != VALID.end())
    {
        long val = std::distance(VALID.begin(),it);
        event = mapIntToEnum(val);
        result = RET::OK;
    }
    return result;
}


/*! \private Cli::parseArg(std::string &input)
     * @brief Test Parses argv and splits into strings.
     * @param input A long input string containing argv from stdin.
     * @return Private vector of strings containing parsed words from stdin.
     */
std::vector<std::string> Cli::parseArg(std::string &input, char delim) {
    std::stringstream m_stream(input);
    std::vector<std::string> seglist;
    std::string segment;
    seglist.reserve(15);
    seglist.clear();

    while(std::getline(m_stream, segment, delim))
    {
        seglist.push_back(segment);
    }
    return seglist;
}

Request Cli::strToRequest(const std::vector<std::string>& vec) {

    Request req(vec.at(1), vec.at(2), vec.at(3), vec.at(4));
    return req;
}

int Cli::verifyParsed(std::vector<std::string> &parsed, Request &req, bool testmode) {

    if(Event::DELETE == req.event || Event::SEARCH == req.event) {
        const auto title = parsed.back();
        if (title.empty()) { return RET::ERROR; }
        req.title = title;
        return verifyExists(title);

    }
    else if (Event::DOWNLOAD == req.event) {
        req.title = parsed.back();
        return verifyDownload(parsed);
    }
    else {
        req = strToRequest(parsed);
        return verifyUpload(parsed);
    }
}

int Cli::verifyExists(const std::string &s) {
    bool result =  JsonParser::getInstance().find(MOVIE, s);
    if(!result) { return RET::ERROR;}
    return RET::OK;
}

int Cli::verifyDownload(std::vector<std::string> &parsed) {

    const auto title = parsed.at(1);
    if (title.empty()) { return false; }

    return verifyExists(title);
}

int Cli::verifyUpload(std::vector<std::string> &parsed) {

    const auto filename = parsed.back();
    if (filename.empty()) { return false; }

    if(access( filename.c_str(), F_OK ) == RET::ERROR) {
        return RET::ERROR;
    }
    std::cout << "To confirm your upload add the following info: \n"
                 "\t <title> <genre> <director> {<actor> <actor>.. }" << std::endl;

    std::string info;
    std::string answer;

    std::getline(std::cin, info);
    auto parsedInfo = parseArg(info, ' ');
    std::cout << "Please confirm <title> " << parsedInfo.front() <<
              "\n <genre> " << parsedInfo.at(1) << " <director> " << parsedInfo.at(2) << " and the following actors: \n" << std::endl;

    for (auto it = parsedInfo.begin() + 2; it != parsedInfo.end(); ++it){
        std::cout << *it << " " << std::endl;
    }

    std::cout << "Y or n? ";
    std::getline(std::cin, answer);
    if(answer.find('n') == std::string::npos)
    {
        return RET::ERROR;
    }
    parsed.push_back(info);
    return RET::OK;
}


/*! \private Cli::printOptions()
 * @brief Test A private method that prints all valid options for stdin.
 */
void Cli::printOptions() {
    std::cout << "\n" << std::endl;

    auto choice {"<choice> = upload, download, search, delete\n"};

    auto upload = "<upload>:<filename> \n\t*<filename> - absolute path to filename. \n";
    auto cmfupload = "\t To confirm your upload add the following info: \n\t <title> <genre> {<actor> <actor>.. } <director>\n\n";

    auto download = "<download>:<movie/series> <title> \n";
    auto cfmdownload = "\t Title exists or did you mean 'abc'? \n\t Download completed\n\n";

    auto search {"<search>:<args>.. \n \t <args>: title, genre, director, list of actors\n"};
    auto cfmsearch = "\t Found the following matches..\n\n";

    auto deleted {"<delete>:<title>\n"};
    auto cfmdelete = "\t Sure you want to delete, Y or n? \n\n";

    auto disconnect = "Write 'exit' to disconnect\n";

    std::cout << choice << "\nExample input..\n\n" << upload << cmfupload << download << cfmdownload << search
    << cfmsearch << deleted << cfmdelete << std::endl;
    std::cout << disconnect << std::endl;
}
