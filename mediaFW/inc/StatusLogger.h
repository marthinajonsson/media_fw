//
// Created by mjonsson on 10/17/18.
//

#ifndef MEDIAFW_STATUSLOGGER_H
#define MEDIAFW_STATUSLOGGER_H


#include "ifc/Logger.h"

class StatusLogger : Logger{
public:

    StatusLogger() = default;
    ~StatusLogger() = default;

    Level_e getEnum(std::string status) override {
        if(status == "OK") {
            return INFO;
        }
        else if (status == "NOK") {
            return ERR;
        }
        return WARN;
    }

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

    void write(Level_e level, std::string output) override{
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
