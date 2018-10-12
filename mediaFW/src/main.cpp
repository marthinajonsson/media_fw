#include <iostream>
#include "Client.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    Client client;
    client.setup();
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
}


TEST(Client, initMovieDb){
    Client client;
    client.setup(); // TODO: mock cli result
    ASSERT_NO_THROW(client.setup());
}
//
//TEST(Client, setup1Client){
//    Client client;
//    client.initiateDatabase(Movie);
//    ASSERT_NO_THROW(client.setup());
//}