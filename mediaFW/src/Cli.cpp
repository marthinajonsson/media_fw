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
    parsed = split(line, ':');
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
            parsed = split(line, ':');
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

// event:category:type:value
// upload:<movie/series>:filename<value>
// download:<movie/series>:title:<value>
// search:<movie/series>:actor/title/genre/director:<value>
// <delete>:<movie/series>:title:<value>
Request Cli::interprete(std::vector<std::string> &input)
{
    Event event = Event::UNDEFINED;
    std::string val;
    std::string type;
    if(RET::ERROR == checkValidEvent(input, event)){
        Request request(RET::ERROR, "No valid event entered");
        return request;
    }

    Request request (event);
    request.setError(RET::OK);


    if(event == Event::EXIT) { return request; }
    else if(event == Event::SSH) {
        return request;
    }

    Category category;
    if(RET::ERROR == checkValidCategory(input, category)){
        request.setError(RET::ERROR);
        request.setErrorDesc("No valid category entered");
        return request;
    }

    request.setCategory(category);

    if(RET::ERROR == getTypeOfValue(input, type))
    {
        request.setError(RET::ERROR);
        request.setErrorDesc("No valid type entered");
        return request;
    }

    if(RET::ERROR == checkValidType(request, type)) {
        request.setError(RET::ERROR);
        request.setErrorDesc("Type not valid to event");
    }

    if(RET::ERROR == getValueOfType(input, val)) {
        request.setError(RET::ERROR);
        request.setErrorDesc("No valid value");
    }


    if(Event::DELETE == event || Event::SEARCH == event || Event::DOWNLOAD == event) {

        if (RET::ERROR == verifyObjectExists(category, val)) {
            request.setError(RET::ERROR);
            request.setErrorDesc("Object does not exists at server or database is unsynced");
            return request;
        }
    }

    if(event == Event::DOWNLOAD || event == Event::DELETE) {
        auto items = JsonParser::getInstance().getLatestFilteredResult();

        if(items.size() == 1) {
            auto item = items.begin()->second;
            setProperties(request, item);
        }
        else {
            request.setMultipleResult(items);
            request.setError(RET::ERROR);
            request.setErrorDesc("More than one item match. Please specify more explictly.");
            return request;
        }
    }
    else if(event == Event::SEARCH) {
        auto items = JsonParser::getInstance().getLatestResult();
        request.setMultipleResult(items);
    }
    else if(Event::UPLOAD == event){
        setFileName(request, val);
    }
    return request;
}

