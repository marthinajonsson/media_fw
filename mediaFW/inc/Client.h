//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H


#include "MovieDatabase.h"
#include "Connection.h"

enum DbType{
    Movie = 2,
    Series = 1
};

class Client {
public:

    Client() = default;
    ~Client() = default;
    DbType type;

    void initiateDatabase(DbType type);
    void handleCliCallback(std::string);
    void setup();

    DbType getCurrentDbType(){
        return this->type;
    }

private:
    Database *db;
    Connection *conn;
};


#endif //MEDIAFW_CLIENT_H
