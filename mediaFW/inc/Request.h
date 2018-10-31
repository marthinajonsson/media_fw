//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_REQUEST_H
#define MEDIAFW_REQUEST_H

#include "Util.h"

class Request {
public:
    Request(Event _event, std::string _title, std::string, std::string _genre, std::string _director, std::vector<std::string> _actors) :
        event(_event), title(_title), genre(_genre), director(_director), actors(_actors) {}

    Request(Event _event, std::string _title) : event(_event), title(_title) {}

    Request(Event _event) : event(_event){}


    ~Request() = default;

    Event event;
    std::string title;
    std::string genre;
    std::string director;
    std::vector<std::string> actors;
};
#endif //MEDIAFW_REQUEST_H
