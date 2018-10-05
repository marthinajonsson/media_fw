#include <iostream>
#include "Client.h"
#include "gtest/gtest.h"


int main() {
    std::cout << "Hello, Worlds!" << std::endl;

    Client client;
    client.setup();

    DbType type = Movie;
    client.initiateDatabase(type);

    if(client.getCurrentDbType() != type){
        std::cout << "type is not working" << std::endl;
    }


    return 0;
}