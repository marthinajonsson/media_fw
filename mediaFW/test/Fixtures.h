//
// Created by mjonsson on 10/12/18.
//

#include <MediaHandler.h>
#include "gtest/gtest.h"

#ifndef MEDIAFW_FIXTURES_H
#define MEDIAFW_FIXTURES_H


class Fixtures : public ::testing::Test {
public:
    Fixtures( ) {
        // initialization code here
    }

    void SetUp( ) {
        MediaHandler mediaHandler;
    }

    void TearDown( ) {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~Fixtures( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
};
#endif //MEDIAFW_FIXTURES_H
