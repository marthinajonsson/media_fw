//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_SUBJECT_H
#define MEDIAFW_SUBJECT_H

#include "Observer.h"

/**
 * Interface for the Subject
 */

class Subject {

public:

    /**
     * Register an observer
     * @param observer the observer object to be registered
     */
    virtual void registerObserver(Observer *observer) = 0;

    /**
     * Unregister an observer
     * @param observer the observer object to be unregistered
     */
    virtual void removeObserver(Observer *observer) = 0;

    /**
     * Notify all the registered observers when a change happens
     */
    virtual void notifyObservers(Event event, std::vector<std::string>&) = 0;

};
#endif //MEDIAFW_SUBJECT_H
