//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H

#include <typeinfo>

#include "MovieDatabase.h"
#include "Connection.h"

enum DbType{
    Movie = 2,
    Series = 1,
    Undefined = 0
};

class Client {
public:

    Client() = default;
    ~Client() = default;
    DbType type;

    void initiateDatabase(DbType type);
    void handleCliCallback(std::vector<std::string>, bool);
    void setup();

    const DbType getCurrentDbType();

private:
    Database *db;
    Connection *conn;
};


#endif //MEDIAFW_CLIENT_H
