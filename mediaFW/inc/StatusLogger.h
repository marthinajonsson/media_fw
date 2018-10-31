//
// Created by mjonsson on 10/17/18.
//

#ifndef MEDIAFW_STATUSLOGGER_H
#define MEDIAFW_STATUSLOGGER_H

#include <fstream>
#include <iostream>
#include "ifc/Logger.h"

class StatusLogger : Logger{
public:

    StatusLogger() {
        logfile.open(getFilename());
    }
    ~StatusLogger() = default;

    void TRACE(Level_e level, std::string message, std::string errorCode) override{
        std::string statusLevel  = m_levelMap.at(level);
        std::string output = statusLevel + message + " (" + errorCode + ") ";
        write(level, output);
    }

    void TRACE(Level_e level, std::string message) override{
        std::string statusLevel  = m_levelMap.at(level);
        std::string output = statusLevel + message;
        write(level, output);
    }

private:
    std::ofstream logfile;

    std::string getFilename () {
        std::chrono::system_clock::time_point time = getDate();
        std::time_t t = system_clock::to_time_t(time);
        std::cout << std::ctime(&t) << std::endl;
        std::string filename = std::ctime(&t) + ".log";
    }

    void write(Level_e level, std::string &output){
        std::string startcode = "\033[";
        std::string endcode = "\033[0m\n";
        if (level == ERR) {
            std::cerr << output << std::endl;
        }
        else if (level == WARN) {

            std::string thecode = "1;93m";
            std::cout << startcode + thecode + output + endcode;
        }
        else {
            std::cerr << output << std::endl;
        }
    }
};


#endif //MEDIAFW_STATUSLOGGER_H
