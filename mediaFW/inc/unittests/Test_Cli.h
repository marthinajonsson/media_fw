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
    Category cat2 = Category::Series;
    Category cat = Category::Movie;
    void SetUp()
    {
        JsonParser::getInstance().load(cat);
        JsonParser::getInstance().load(cat2);
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
    ASSERT_TRUE(act.size() == 2);
    ASSERT_FALSE(output.getError() == RET::ERROR);
}

TEST_F(CliTest, CliTest_Download3__Test) {
    std::string test = "download:genre:Romance";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getError() == RET::ERROR);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getMultipleResult().size() > 1);
    for(auto result : output.getMultipleResult()) {
        for (auto s : result.second ) {
            std::cout << s << std::endl;
        }
        std::cout << "\n";
    }
}

TEST_F(CliTest, CliTest_Download4__Test) {
    std::string test = "download:genre:Mystery";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getMultipleResult().size() == 0);
    ASSERT_TRUE(output.getTitle() == "11.22.63");
    ASSERT_TRUE(output.getGenre() == "Mystery");
    ASSERT_TRUE(output.getDirector() == "James Franco");
    ASSERT_TRUE(output.getActors().size() == 1);
}


TEST_F(CliTest, CliTest_Search_Test) {
    std::string test = "search:movie:genre:Romance";
    auto output = cli->process(test);
    auto items = output.getMultipleResult();

    ASSERT_TRUE(items.size() == 2);
    for(auto i : items) {
        auto g = i.second.at(1);
        ASSERT_TRUE(g == "Romance");
    }
}
//
//TEST_F(CliTest, CliTest_Search2_Test) {
//
//}
//
//TEST_F(CliTest, CliTest_Search3_Test) {
//
//}
//
//TEST_F(CliTest, CliTest_Upload_Test) {
//
//}
//
//TEST_F(CliTest, CliTest_Upload2_Test) {
//
//}
//
//TEST_F(CliTest, CliTest_Upload3_Test) {
//
//}

//TODO: add delete test cases

TEST_F(CliTest, CliTest_EXIT_Test)
{
    std::string line = "exit";
    auto output = cli->process(line);
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getEvent() == Event::EXIT);
}


#endif //MEDIAFW_TEST_CLI_H
