//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_TEST_CLI_H
#define MEDIAFW_TEST_CLI_H
#include "gmock/gmock.h"

#include "Cli.h"
#include "JsonParser.h"

class CliTest : public ::testing::Test
{
protected:

    Cli* cli;
    void SetUp()
    {
        JsonParser::getInstance().load();
    }

    void TearDown()
    {
        JsonParser::getInstance().clearMap();
    }
};



TEST_F(CliTest, CliTest_Upload_Test) {

    std::string test = "upload:testfile.txt";
    auto output = cli->process(test);
    ASSERT_TRUE(output.front() == "upload");
}


TEST_F(CliTest, CliTest_Download_Test) {

    std::string test = "download:The Proposal";
    auto output = cli->process(test);
    ASSERT_TRUE(output.front() == "download");
}

TEST_F(CliTest, CliTest_Download2_Test) {
    std::string test = "download:Thomas Beaudoin";
    auto output = cli->process(test);
    ASSERT_TRUE(output.front() == "download");
}

TEST_F(CliTest, CliTest_Search__Test) {
    std::string test = "search:Sandra Bullock";
    auto output = cli->process(test);
    ASSERT_TRUE(output.front() == "search");
}

#endif //MEDIAFW_TEST_CLI_H
