#include <iostream>
#include "Client.h"
#include "Test_Database.h"
#include "gtest/gtest.h"
#include "MediaHandler.h"



int main(int argc, char **argv) {
    //Client client;
    //client.setup();
    MediaHandler mediaHandler;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

// TODO: divide into submodules to allow better structure and unit tests
// TODO: install gmock
// TODO: consider removing vector<string> and just add strings


