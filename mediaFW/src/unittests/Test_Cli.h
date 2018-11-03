//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_TEST_CLI_H
#define MEDIAFW_TEST_CLI_H
//#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Cli.h"
#include "JsonParser.h"

class CliTest : public ::testing::Test
{
protected:

    Cli* cli;
    Category cat = Category::Movie;
    void SetUp()
    {
        JsonParser::getInstance().load(cat);
    }

    void TearDown()
    {
        JsonParser::getInstance().clear();
    }
};


TEST_F(CliTest, CliTest_Download_Test) {

    std::string test = "download:The Proposal";
    auto output = cli->process();
    ASSERT_TRUE(output.m_event == Event::DOWNLOAD);
}

TEST_F(CliTest, CliTest_Download2_Test) {
    std::string test = "download:Thomas Beaudoin";
    auto output = cli->process();
    ASSERT_TRUE(output.m_event == Event::DOWNLOAD);
}

TEST_F(CliTest, CliTest_Search__Test) {
    std::string test = "search:Sandra Bullock";
    auto output = cli->process();
    ASSERT_TRUE(output.m_event == Event::DOWNLOAD);
}

#endif //MEDIAFW_TEST_CLI_H
