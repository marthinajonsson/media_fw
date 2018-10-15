//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H

#include "MovieDatabase.h"
#include "Connection.h"
#include "Cli.h"


class Client {
public:

    /*! \public Client constructor()
    * @brief Instantiates database type DbType_e and corresponding Database.
    */
    Client() {
        type = Movie;
        p_db = new MovieDatabase();
        p_db->printAll();
    };

    /*! \public Client deconstructor()
    * @brief deletes previous instantiated Database.
    */
    ~Client() {
        delete p_db;
    };

    /*! \enum Client::DbType_e
    * @brief Enum describing database type.
    */
    enum DbType_e{
        Movie = 2,
        Series = 1,
        Undefined = 0
    }type;

    /*! \public Client::setup()
    * @brief A method that waits for input from private method Client::getCliInput().
    * The method will break if input is interpreted as exit or
    * continues by having the request handled in Client::handleCallback().
    */
    void setup();

private:
    /*! \privatesection Client *p_db
    * @brief Private pointer ot Database object.
    */
    Database *p_db;
    /*! \privatesection Database* p_db
     * @brief Private pointer to database object.
     */
    Connection *p_conn;
    /*! \privatesection Cli* p_cli.
     * @brief Private pointer to a cli object
     */
    Cli *p_cli;


    /*! \privatesection Client::getCliInput(Cli* p_cli)
     * @brief A method that waits for CLI to process incoming request. Used by std::future.
     * @param p_cli
     * @return A vector of strings containing the result of CLI process
     */
    static std::vector<std::string> getCliInput(Cli* p_cli) {
        return p_cli->process();
    }

    /*! \privatesection Client::handleCallback(std::vector<std::string request , bool connected)
     * @brief handles the clients requests to the server.
     * @param request - String containing all information needed for the server request.
     * @param connected - Boolean parameter indicating we have an established ssh connection.
     */
    void handleCallback(std::vector<std::string> request, bool connected);
};


#endif //MEDIAFW_CLIENT_H
