#include <iostream>
#include "Client.h"
#include "gtest/gtest.h"


int main() {
    std::cout << "Hello, Worlds!" << std::endl;

    Client client;
    DbType type = Movie;
    client.initiateDatabase(type);

    if(client.getCurrentDbType() != type){
        std::cout << "type is not working" << std::endl;
    }

    client.setup();
    return 0;
}