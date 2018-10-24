//
// Created by mjonsson on 10/17/18.
//

#ifndef MEDIAFW_LOGGER_H
#define MEDIAFW_LOGGER_H

#endif //MEDIAFW_LOGGER_H

#include <iostream>
#include <map>

class Logger {
public:
    enum Level_e{ INFO = 0, ERR = 1, WARN = 2 } level;

    std::map<Level_e, const char*> m_levelMap;

    Logger () {
        map_init(m_levelMap)
                (INFO, "[INFO] ")
                (ERR, "[ERROR] ")
                (WARN, "[WARN] ")
                ;
    }
    ~Logger() = default;

    virtual void TRACE(Level_e level , std::string message) = 0;
    virtual Level_e getEnum(std::string) = 0;

protected:

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

