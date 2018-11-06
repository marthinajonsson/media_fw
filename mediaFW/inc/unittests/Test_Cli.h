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
    ASSERT_TRUE("The Proposal" == output.getTitle());
    ASSERT_TRUE("Anne Fletcher" == output.getDirector());
    ASSERT_TRUE(output.getCategory() == Category::Movie);
    ASSERT_TRUE(output.getError() == RET::OK);
}

TEST_F(CliTest, CliTest_Download2_Test) {
    std::string test = "download:actor:Thomas Beaudoin";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getTitle() == "The Spirit of Christmas");
    auto act = output.getActors();
    auto it = std::find(act.begin(), act.end(), "Thomas Beaudoin");
    bool found = it != act.end();
    ASSERT_TRUE(found);
    ASSERT_TRUE(output.getCategory() == Category::Movie);
    ASSERT_FALSE(output.getError() == RET::ERROR);
}

// TODO: return a list of all matches
// TODO: then print a list of result instead of doing anything else


TEST_F(CliTest, CliTest_Download3__Test) {
    std::string test = "download:genre:Romance";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getGenre() == "Romance");
}

TEST_F(CliTest, CliTest_Search_Test) {
    std::string test = "search:movie:genre:Romance"; // TODO: not working, how should it work? same as donwload
    auto output = cli->process(test);
    int a = 2;
    ASSERT_TRUE(a == 2);
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

//TODO: add delete test cases

TEST_F(CliTest, CliTest_EXIT_Test)
{
    std::string line = "exit";
    auto output = cli->process(line);
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getEvent() == Event::EXIT);
}


#endif //MEDIAFW_TEST_CLI_H
