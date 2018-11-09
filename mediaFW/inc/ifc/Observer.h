//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_OBSERVER_H
#define MEDIAFW_OBSERVER_H

#include <string>
#include <vector>
#include <Request.h>


class Observer {

public:

    Observer() = default;
    ~Observer() = default;


    /**
     * Update the state of this observer
     * @param temp new temperaure
     * @param humidity new humidity
     * @param pressure new pressure
     */
    virtual int update(Request&) = 0;

};

#endif //MEDIAFW_OBSERVER_H
