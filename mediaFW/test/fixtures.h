//
// Created by mjonsson on 10/12/18.
//
#include <Client.h>
#include "gtest/gtest.h"

#ifndef MEDIAFW_FIXTURES_H
#define MEDIAFW_FIXTURES_H


class fixtures : public ::testing::Test {
public:
    fixtures( ) {
        // initialization code here
    }

    void SetUp( ) {
        Client client;
        client.setup();
    }

    void TearDown( ) {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~fixtures( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
};
#endif //MEDIAFW_FIXTURES_H
