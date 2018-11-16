//
// Created by mjonsson on 10/16/18.
//



#ifndef MEDIAFW_UTIL_H
#define MEDIAFW_UTIL_H

#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>

/*! \section Common Enums
 *  \enum RET
 *  \brief Defines results from operations
 *  \var RET::OK Operation went well without any known errors
 *  \var RET::ERROR Operation ended unexpectedly with errors
 */
enum RET {
    OK = 0,
    ERROR = -1
};


/*! \section Common Enums
 *  \enum ORDER
 *  \brief Defines the order of common properties that is saved in vectors
 *  throughout the code.
 *  \var TITLE_POS the position of the property @property title
 *  \var GENRE_POS the position of the property @property genre
 *  \var DIRECTOR_POS the position of the property @property director
 *  \var ACTORS_POS the start position of the property @property actors
 */
enum ORDER {
    TITLE_POS = 0,
    GENRE_POS = 1,
    DIRECTOR_POS = 2,
    ACTORS_POS = 3
};


/*! \section Common Enums
 *  \enum Category
 *  \brief Defines the category of incoming request and helps to sort the database items
 *  \var Category::Movie user requested an operation on movies
 *  \var Category::Series user requested an operation on series
 */
enum Category {
    Movie = 0,
    Series = 1,
    Config = 2,
    All = 3
};


/*! \section Common Enums
 *  \enum Progress
 *  \brief Defines the progress of incoming user request
 *  \var Progress::To do request have not been processed yet
 *  \var Progress::InProgress request is being processed
 *  \var Progress:Done request has been processed
 */
enum Progress {
    Todo,
    InProgress,
    Done
};


/*! \section Common Enums
 *  \enum Event
 *  \brief Defines the event derived from user CLI input
 *  \var Event::UPLOAD user request an file upload
 *  \var Event::DOWNLOAD user request an file download
 *  \var Event::SEARCH user request an file search
 *  \var Event::DELETE user request to delete a file
 *  \var Event::HELP user request help
 *  \var Event::EXIT user requested to exit
 *  \var Event::UNDEFINED no request have been made or it can not be identified
 */
enum Event {
    UPLOAD = 0,
    DOWNLOAD = 1,
    SEARCH = 2,
    DELETE = 3,
    HELP = 4,
    LIST = 5,
    STREAM = 6,
    EXIT = 7,
    SSH = 8,
    UNDEFINED = 9
};


template <typename T>
inline Event castTypeToEvent( T& val ) {
    return static_cast<Event>(val);
}

template <typename T>
inline Category castTypeToCategory( T& val ) {
    return static_cast<Category >(val);
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}

/*! \struct map_init_helper
* @brief map @Level_e to std::string in @m_levelMap
* @tparam T type of enum
*/
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

/*! \protected map_init
* @brief wrapper for @struct map_init_helper
* @tparam T type of enum
* @param item the enum
* @return type usually std::strings
*/
template<typename T> map_init_helper<T> map_init(T& item)
{
    return map_init_helper<T>(item);
}

#endif //MEDIAFW_UTIL_H
