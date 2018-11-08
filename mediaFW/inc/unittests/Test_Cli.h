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
    std::string FILE_DIR = "~/repo/media_fw/mediaFW/data/";
    std::string TEST_FILE = FILE_DIR + "testfile.txt";
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
    ASSERT_TRUE(output.getErrorDesc().empty());
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

TEST_F(CliTest, CliTest_Search2_Test) {
    std::string test = "search:series:genre:Romance";
    auto output = cli->process(test);
    auto items = output.getMultipleResult();
    auto err = output.getError();
    auto desc = output.getErrorDesc();

    ASSERT_TRUE(items.empty());
    ASSERT_TRUE(err == RET::OK);
    ASSERT_TRUE(desc.empty());
}

TEST_F(CliTest, CliTest_Search3_Test) {
    std::string test = "search:series:director:James Franco";
    auto output = cli->process(test);
    auto items = output.getMultipleResult();
    auto err = output.getError();
    auto desc = output.getErrorDesc();

    ASSERT_TRUE(items.size() == 1);
    ASSERT_TRUE(err == RET::OK);
    ASSERT_TRUE(desc.empty());
}

TEST_F(CliTest, CliTest_Upload_Test) {
    std::string test = "upload:series:filename:" + TEST_FILE;
    std::vector<std::string> test2 = {"test_title","horror","test_director","test_actor"};
    auto compare = test2;
    auto output = cli->process(test);
    cli->verifyUploadTest(output, test2);
    auto t = output.getTitle();
    ASSERT_TRUE(output.getTitle() == compare.front());
    ASSERT_TRUE(output.getGenre() == compare.at(1));
    ASSERT_TRUE(output.getDirector() == compare.at(2));
    ASSERT_TRUE(output.getActors().size() == 1);
    ASSERT_TRUE(output.getActors().front() == compare.back());
    ASSERT_TRUE(output.getCategory() == Category::Series);
}

TEST_F(CliTest, CliTest_Upload2_Test) {
    std::string test = "upload:movie:filename:" + TEST_FILE;
    std::vector<std::string> test2 = {"test_title","horror","test_director","test_actor"};
    auto compare = test2;
    auto output = cli->process(test);
    cli->verifyUploadTest(output, test2);
    auto t = output.getTitle();
    ASSERT_TRUE(output.getTitle() == compare.front());
    ASSERT_TRUE(output.getGenre() == compare.at(1));
    ASSERT_TRUE(output.getDirector() == compare.at(2));
    ASSERT_TRUE(output.getActors().size() == 1);
    ASSERT_TRUE(output.getActors().front() == compare.back());
    ASSERT_TRUE(output.getCategory() == Category::Movie);
}

TEST_F(CliTest, CliTest_Delete_Test) {
    std::string test = "delete:title:The Proposal";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DELETE);
    ASSERT_TRUE("The Proposal" == output.getTitle());
    ASSERT_TRUE("Anne Fletcher" == output.getDirector());
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getErrorDesc().empty());
}

TEST_F(CliTest, CliTest_Delete2_Test) {
    std::string test = "delete:title:Dummy";
    auto output = cli->process(test);
    ASSERT_TRUE(output.getEvent() == Event::DELETE);
    ASSERT_FALSE("Anne Fletcher" == output.getDirector());
    ASSERT_FALSE(output.getError() == RET::OK);
    ASSERT_FALSE(output.getErrorDesc().empty());
}

TEST_F(CliTest, CliTest_EXIT_Test)
{
    std::string line = "exit";
    auto output = cli->process(line);
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getEvent() == Event::EXIT);
}


#endif //MEDIAFW_TEST_CLI_H
