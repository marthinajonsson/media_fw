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

TEST_F(RequestTest, RequestTest_Title_Test) {
    Request request;
    request.setProperties("testT", "testG", "testD");
    auto func = request.commands.at(TITLE);
    auto s = func();
    auto t = request.getMetadata().m_title;
    ASSERT_TRUE(t == "testT");
}
#endif //MEDIAFW_TEST_REQUEST_H
