//
// Created by root on 11/22/18.
//

#ifndef MEDIAFW_TEST_REQUEST_H
#define MEDIAFW_TEST_REQUEST_H

#include <string>

#include "Request.h"
#include "gtest/gtest.h"

class RequestTest : public ::testing::Test
{
protected:

    std::string FILE_DIR = "~/repo/media_fw/mediaFW/data/";
    std::string TEST_FILE = FILE_DIR + "testfile.txt";

    void SetUp() override
    {
//        cli = new Cli;
    }

    void TearDown() override
    {
//        delete cli;
    }
};

TEST_F(RequestTest, RequestTest_Construct1_Test) {
    Request request;
    std::string t = "testT";
    std::string g = "testG";
    std::string d = "testD";
    request.set(TITLE, t);
    request.set(GENRE, g);
    request.set(DIRECTOR, d);
    request.setActors({"act1", "act2"});
    t = request.get(TITLE);
    g = request.get(GENRE);
    d = request.get(DIRECTOR);
    auto a = request.get(ACTOR);
    ASSERT_TRUE(t == "testT");
    ASSERT_TRUE(g == "testG");
    ASSERT_TRUE(d == "testD");
    ASSERT_TRUE(a == "act1");

}

TEST_F(RequestTest, RequestTest_Construct2_Test) {
    Request request(Event::SEARCH);
    ASSERT_TRUE(request.getEvent() == Event::SEARCH);

}
#endif //MEDIAFW_TEST_REQUEST_H
