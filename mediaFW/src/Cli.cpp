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
    Category category = Category::Movie;
    Event event;

    if(RET::ERROR == checkValidEvent(input, event)){  // search, upload, download
        Request request(RET::ERROR);
        return request;
    }

    Request request (event);
    if(event == Event::SEARCH) {
        auto cat = input.front();

        if(cat == SERIES) {
            category = Category::Series;
        }
        request.setCategory(category);
        pop_front(input);
    }
    auto type = getType(request, input);  // title, genre, actor and so on..
    if (type.empty()) {
        request.setError(RET::ERROR);
        return request;
    }


    if(Event::DELETE == event || Event::SEARCH == event || Event::DOWNLOAD == event) {

        if (RET::ERROR == verifyObjectExists(type, input.front())) {
            request.setError(RET::ERROR);
            return request;
        }
    }

    if(event == Event::DOWNLOAD || event == Event::DELETE) {

        auto items = JsonParser::getInstance().getLatestResult();

        if(items.size() == 1) {
            auto item = items.begin()->second;
            setProperties(request, item, type);
        }
        else {
            request.setMultipleResult(items);
            request.setError(RET::ERROR);
            return request;
        }
    }
    else if(event == Event::SEARCH) {
        auto items = JsonParser::getInstance().getLatestResult();
        request.setMultipleResult(items);
    }
    else if(Event::UPLOAD == event){
        setFileName(request, input, type);

        if(RET::ERROR == verifyUpload(request)) {
            request.setError(RET::ERROR);
            return request;
        }
    }
    return request;
}

