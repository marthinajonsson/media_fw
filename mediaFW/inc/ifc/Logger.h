//
// Created by mjonsson on 10/17/18.
//

#ifndef MEDIAFW_LOGGER_H
#define MEDIAFW_LOGGER_H

#endif //MEDIAFW_LOGGER_H

#include <iostream>
#include <map>
#include <ctime>

class Logger {
public:
    static enum Level_e{ INFO = 0, ERR = 1, WARN = 2 } level;

    std::map<Level_e, const char*> m_levelMap;

    Logger () {
        map_init(m_levelMap)
                (INFO, "[INFO] ")
                (ERR, "[ERROR] ")
                (WARN, "[WARN] ")
                ;
    }
    ~Logger() = default;

    virtual void TRACE(Level_e level , std::string message, std::string errorCode) = 0;
    virtual void TRACE(Level_e level , std::string message) = 0;

protected:
    std::string getDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        auto year = 1900 + ltm->tm_year;
        auto month = 1 + ltm->tm_mon;
        auto day = ltm->tm_mday;
        std::string y = std::to_string(year);
        std::string m = std::to_string(month);
        std::string d = std::to_string(day);
        y = y.append("-");
        m = m.append("-");
        return y + m + d;
    }

    std::string getTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int hour = 1 + ltm->tm_hour;
        auto min = 1 + ltm->tm_min;
        auto sec = 1 + ltm->tm_sec;
        std::string h = std::to_string(hour);
        std::string m = std::to_string(min);
        std::string s = std::to_string(sec);
        h = h.append(":");
        m = m.append(":");
        return h + m + s;
    }


    template<typename T> struct map_init_helper
    {
        T& data;
        map_init_helper(T& d) : data(d) {}
        map_init_helper& operator() (typename T::key_type const& key, typename T::mapped_type const& value)
        {
            data[key] = value;
            return *this;
        }
    };

    template<typename T> map_init_helper<T> map_init(T& item)
    {
        return map_init_helper<T>(item);
    }

};

