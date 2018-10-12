//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H

#include <typeinfo>

#include "MovieDatabase.h"
#include "Connection.h"
#include "Cli.h"

enum DbType{
    Movie = 2,
    Series = 1,
    Undefined = 0
};

class Client {
public:

    Client() {
        type = Movie;
        p_db = new MovieDatabase();
    };
    ~Client() {
        delete p_db;
    };
    DbType type;
    void setup();

private:
    Database *p_db;
    Connection *p_conn;
    Cli *p_cli;

    void handleCliCallback(std::vector<std::string>, bool);
};


#endif //MEDIAFW_CLIENT_H
