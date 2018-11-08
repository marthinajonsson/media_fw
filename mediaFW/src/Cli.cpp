//
// Created by mjonsson on 9/30/18.
//


#include <iostream>
#include <sstream>
#include <iterator>

#include "Cli.h"
#include <JsonParser.h>

/*! \class Cli cli.h "inc/cli.h"
 *  \brief Class implementing the functionality of a command line interface.
 *
 * Receives inputs from STDIN and splits the result into strings.
 */

Request Cli::process(std::string &_line) {
    std::vector<std::string> parsed;
    parsed = parseArg(_line, ':');
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

            if(request.getEvent() == Event::UPLOAD)
            {
                if(RET::ERROR == verifyUpload(request)) {
                    request.setError(RET::ERROR);
                    return request;
                }
            }
            return request;
        }
    }
    return Request(RET::ERROR, "Cli session ended unexpected");
}

Request Cli::interprete(std::vector<std::string> &_input)
{
    Event event;
    std::string cat;
    if(RET::ERROR == checkValidEvent(_input, event)){  // search, upload, download
        Request request(RET::ERROR, "No valid event entered");
        return request;
    }

    Request request (event);
    request.setError(RET::OK);

    if(event == Event::SEARCH || event == Event::UPLOAD) {

        cat = setSearchCategory(request, _input);
    }

    auto type = getType(request, _input);  // title, genre, actor and so on..
    if (type.empty()) {
        request.setError(RET::ERROR);
        request.setErrorDesc("Type not valid");
        return request;
    }


    if(Event::DELETE == event || Event::SEARCH == event || Event::DOWNLOAD == event) {

        if (RET::ERROR == verifyObjectExists(type, _input.front())) {
            request.setError(RET::ERROR);
            request.setErrorDesc("Object does not exists at server or database is unsynced");
            return request;
        }
    }

    if(event == Event::DOWNLOAD || event == Event::DELETE) {
        auto items = JsonParser::getInstance().getLatestResult();

        if(items.size() == 1) {
            auto item = items.begin()->second;
            setProperties(request, item, true);
        }
        else {
            request.setMultipleResult(items);
            request.setError(RET::ERROR);
            request.setErrorDesc("More than one item match. Please specify more explictly.");
            return request;
        }
    }
    else if(event == Event::SEARCH) {
        auto items = filterResult(cat);
        request.setMultipleResult(items);
    }
    else if(Event::UPLOAD == event){
        setFileName(request, _input, type);
    }
    return request;
}

