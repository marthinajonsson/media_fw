//
// Created by mjonsson on 9/30/18.
//


#include <iostream>
#include <sstream>
#include <unistd.h>
#include <iterator>

#include "Cli.h"
#include <JsonParser.h>

/*! \class Cli cli.h "inc/cli.h"
 *  \brief Class implementing the functionality of a command line interface.
 *
 * Receives inputs from STDIN and splits the result into strings.
 */

Request Cli::process(std::string &line) {
    std::vector<std::string> parsed;
    parsed = parseArg(line, ':');
    Request request = interprete(parsed);
    return request;
}

Request Cli::process()
{
    std::vector<std::string> parsed;
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
            Request request = interprete(parsed);
            return request;
        }
    }
    return Request(RET::ERROR);
}

Request Cli::interprete(std::vector<std::string> &input)
{
    Event event;
    int res;

    if(RET::ERROR == checkValidEvent(input.front(), event)){  // search, upload, download
        Request request(RET::ERROR);
        return request;
    }

    Request request (event);
    pop_front(input); // remove interpreted arg //TODO: this changes order for type and value [The Proposal][title]

    auto type = getType(request, input);  // title, genre, actor and so on..
    if (type.empty()) {
        request.setError(RET::ERROR);
        return request;
    }

    if(type == "title") {
        request.setTitle(input.front());
    }

    if(event == Event::UPLOAD || type == "filename") {
        request.setFilename(type);
        pop_front(input); // remove title or filename
    }

    if(Event::DELETE == event || Event::SEARCH == event || Event::DOWNLOAD == event) {
        if(RET::ERROR == verifyExists(request, type, input)) {
            request.setError(RET::ERROR);
            return request;
        }
    }
    else {
        if(RET::ERROR == verifyUpload(request)) {
            request.setError(RET::ERROR);
            return request;
        }
    }
    return request;
}


int Cli::verifyUpload(Request &req) {

    const auto filename = req.getFileName();
    if (filename.empty()) { return false; }
    if(access( filename.c_str(), F_OK ) == RET::ERROR) {
        req.setError(RET::ERROR);
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
    req.setTitle(parsedInfo.front());
    pop_front(parsedInfo);
    req.setGenre(parsedInfo.front());
    pop_front(parsedInfo);
    req.setDirector(parsedInfo.front());
    pop_front(parsedInfo);
    req.setActors(parsedInfo);
    return RET::OK;
}




