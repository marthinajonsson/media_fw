//
// Created by mjonsson on 10/3/18.
//



#ifndef MEDIAFW_DATABASE_H
#define MEDIAFW_DATABASE_H

 /// <summary>
/// A module that works as an interface for subclasses and let them perform database actions
/// </summary>


#include "DatabaseItem.h"
#include "JsonParser.h"
#include <list>
#include <iostream>
#include <mutex>
#include <future>
#include <thread>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException() : std::logic_error("Function not yet implemented") { };
};


/*! \class Database base class.
 * @brief Defines methods for database implementations.
 */
class Database {
public:

    /*! \public Database()
     * @brief Default constructor.
     */
    Database() = default;
    /*! \public ~Database()
     * @brief Default deconstructor.
     */
    ~Database() = default;

    /*! \public Database::syncDatabase()
     * @brief Sync info from json file and saves it to a list of database objects.
     */
    virtual void syncLocalDatabase() = 0;

    /// <summary>
    /// Uploads the requested database item.
    /// </summary>
    /// <param>A const reference to a database item</param>
    virtual void pushItem(const DatabaseItem &m_item) = 0;

    /// <summary>
    /// Fetch the requested database item.
    /// </summary>
    /// <param>A const reference to a title</param>
    /// <returns>The requested DatabaseItem</returns>
    virtual DatabaseItem fetchItem(const std::string &title) = 0;

    /// <summary>
    /// Delete the requested database item.
    /// </summary>
    /// <param>A const reference to a database item</param>
    virtual void purgeItem(const DatabaseItem &m_item) = 0;

    /// <summary>
    /// Prints the entire database content.
    /// </summary>s
    virtual void printAll() = 0;

    /// <summary>
    /// Method that return the size of the database.
    /// </summary>
    /// <returns>Size of the database (long).</returns>
    virtual long getNumberOfItem() = 0;


protected:
    /// <summary>
    /// A protected list of DatabaseItems.
    /// </summary>
    std::list<DatabaseItem> m_items;
    /// <summary>
    /// A protected vector of strings with info for the DatabaseItems.
    /// </summary>
    std::map<std::string, metadata>  m_saved;
    /// <summary>
    /// A protected mutex for threadsafe r/w of DatabaseItems.
    /// </summary>
    mutable std::mutex m_lock;
    /// <summary>
    /// A protected condittion variable for the mutex and Database list.
    /// </summary>
    std::condition_variable m_emptyList;
};


#endif //MEDIAFW_DATABASE_H
