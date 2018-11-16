//
// Created by mjonsson on 11/16/18.
//

#ifndef MEDIAFW_TEST_HTTPCONNECTOR_H
#define MEDIAFW_TEST_HTTPCONNECTOR_H

#include <HttpConnector.h>
#include "gtest/gtest.h"

class HttpTest : public ::testing::Test
{
protected:

    void SetUp() override
    {
        std::cout << "setup" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "teardown" << std::endl;
    }
};

TEST_F(HttpTest, HttpTest_Search_Test) {
    HttpConnector p_hconn;
    Request request;
    request.setEvent(Event::SEARCH);
    request.setError(RET::OK);
    request.setCategory(Category::Movie);
    request.setGenre("Romance");

    std::string expected = "syno vs searchMovie --payload '{genre:Romance}' --url TestUser:abc@192.168.0.107:5000 --pretty";
    auto result = p_hconn.compile(request);
    ASSERT_TRUE(expected == result);
};
#endif //MEDIAFW_TEST_HTTPCONNECTOR_H
