//
// Created by mjonsson on 10/12/18.
//

#ifndef MEDIAFW_TESTCLASS_H
#define MEDIAFW_TESTCLASS_H

#include "fixtures.h"
#include "mocks.h"

TEST(Client, handleStartup){
    Client client;
    ASSERT_NO_THROW(client.setup());
}

 
TEST_F (fixtures, handleStartup) {
    ASSERT_TRUE(1==1);
}


#endif //MEDIAFW_TESTCLASS_H
