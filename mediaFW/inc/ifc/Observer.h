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
     * @param Request of update
     */
    virtual int update(Request&) = 0;
};

#endif //MEDIAFW_OBSERVER_H
