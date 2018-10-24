//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_OBSERVER_H
#define MEDIAFW_OBSERVER_H

#include <string>
#include <vector>

enum class Event { UPLOAD = 1, DOWNLOAD = 2, SEARCH, DELETE, HELP, EXIT };

class Observer {

public:

    /**
     * Update the state of this observer
     * @param temp new temperaure
     * @param humidity new humidity
     * @param pressure new pressure
     */
    virtual void update(Event event, std::vector<std::string> &info) = 0;

};

#endif //MEDIAFW_OBSERVER_H
