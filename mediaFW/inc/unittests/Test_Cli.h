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

    std::string test = "download:title:The Proposal";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    auto t = output.getTitle();
    ASSERT_TRUE(output.getTitle() == t);
    ASSERT_TRUE(output.getCategory() == Category::Movie);
    ASSERT_TRUE(output.getError() == RET::OK);
}

TEST_F(CliTest, CliTest_Download2_Test) {
    std::string test = "download:actor:Thomas Beaudoin";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getTitle() == "The Spirit of Christmas"); //TODO: title is set to what is searched. In this case Thomas Beauodin.
    ASSERT_TRUE(output.getCategory() == Category::Movie);
    ASSERT_TRUE(output.getError() == RET::ERROR);
}

TEST_F(CliTest, CliTest_Download3__Test) {
    std::string test = "download:genre:Romance"; //TODO: should not work if more than 1 hit, then search should be used.
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
}

TEST_F(CliTest, CliTest_Search_Test) {

}

TEST_F(CliTest, CliTest_Search2_Test) {

}

TEST_F(CliTest, CliTest_Search3_Test) {

}

TEST_F(CliTest, CliTest_Upload_Test) {

}

TEST_F(CliTest, CliTest_Upload2_Test) {

}

TEST_F(CliTest, CliTest_Upload3_Test) {

}

TEST_F(CliTest, CliTest_EXIT_Test)
{
    std::string line = "exit";
    auto output = cli->process(line);
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getEvent() == Event::EXIT);
}


#endif //MEDIAFW_TEST_CLI_H
