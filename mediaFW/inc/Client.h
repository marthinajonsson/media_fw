//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H


#include "Database.h"
#include "MovieDatabase.h"

class Client {
public:

    Client() = default;
    ~Client() = default;

    enum DbType{
        Movie = 2,
        Series = 1
    };

    void initiateDatabase(DbType type);




};


#endif //MEDIAFW_CLIENT_H
