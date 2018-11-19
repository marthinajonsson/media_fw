//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_TEST_CLI_H
#define MEDIAFW_TEST_CLI_H

#include "gtest/gtest.h"
#include "Cli.h"
#include "Request.h"
#include "JsonParser.h"

class CliTest : public ::testing::Test
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


TEST_F(CliTest, CliTest_Download_Test) {
    std::string test = "download:movie:title:The Proposal";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    Request output;
    output = cli.process(test);
    auto e = output.getEvent();
    auto t = output.getTitle();
    auto dir = output.getDirector();
    auto err = output.getError();
    auto errStr = output.getErrorDesc();
    ASSERT_TRUE(e == Event::DOWNLOAD);
    //ASSERT_TRUE("The Proposal" == t);
    ASSERT_TRUE("Anne Fletcher" == dir);
    ASSERT_TRUE(err == RET::OK);
    ASSERT_TRUE(errStr.empty());
}

TEST_F(CliTest, CliTest_Download2_Test) {
    std::string test = "download:movie:actor:Thomas Beaudoin";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    auto output = cli.process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getTitle() == "The Spirit of Christmas");
    auto act = output.getActors();
    auto it = std::find(act.begin(), act.end(), "Thomas Beaudoin");
    bool found = it != act.end();
    ASSERT_TRUE(found);
    ASSERT_TRUE(act.size() == 2);
    ASSERT_TRUE(output.getError() == RET::ERROR);
}

TEST_F(CliTest, CliTest_Download3__Test) {
    std::string test = "download:movie:genre:Romance";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    auto output = cli.process(test);
    ASSERT_TRUE(output.getError() == RET::ERROR);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getMultipleResult().size() > 1);
}

TEST_F(CliTest, CliTest_Download4__Test) {
    std::string test = "download:series:genre:Mystery";
    JsonParser::getInstance().load(Category::Series);
    Cli cli;
    auto output = cli.process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getMultipleResult().size() == 0);
    ASSERT_TRUE(output.getTitle() == "11.22.63");
    ASSERT_TRUE(output.getGenre() == "Mystery");
    ASSERT_TRUE(output.getDirector() == "James Franco");
    ASSERT_TRUE(output.getActors().size() == 1);
}


TEST_F(CliTest, CliTest_Search_Test) {
    std::string test = "search:movie:genre:Romance";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    auto output = cli.process(test);
    auto items = output.getMultipleResult();

    ASSERT_TRUE(items.size() == 2);
    for(auto i : items) {
        auto g = i.second.getGenre();
        ASSERT_TRUE(g == "Romance");
    }
}

TEST_F(CliTest, CliTest_Search2_Test) {
    Cli cli;
    std::string test = "search:series:genre:Romance";
    JsonParser::getInstance().load(Category::Series);
    auto output = cli.process(test);
    ASSERT_TRUE(output.getError() == RET::ERROR);
    auto items = output.getMultipleResult();
    ASSERT_TRUE(items.empty());
}

TEST_F(CliTest, CliTest_Search3_Test) {
    std::string test = "search:series:director:James Franco";
    JsonParser::getInstance().load(Category::Series);
    Cli cli;
    auto output = cli.process(test);
    auto items = output.getMultipleResult();
    auto err = output.getError();
    auto desc = output.getErrorDesc();

    ASSERT_TRUE(items.size() == 1);
    ASSERT_TRUE(err == RET::OK);
    ASSERT_TRUE(desc.empty());
}

TEST_F(CliTest, CliTest_Upload_Test) {
    Cli cli;
    std::string test = "upload:series:filename:" + TEST_FILE;
    Metadata meta("test", "horror", "dtest", {"test_act"}, Category::Series);
    JsonParser::getInstance().load(Category::Series);
    auto output = cli.process(test);
    cli.verifyUploadTest(output, meta);
    ASSERT_TRUE(output.getTitle() == meta.getTitle());
    ASSERT_TRUE(output.getGenre() == meta.getGenre());
    ASSERT_TRUE(output.getDirector() == meta.getDirector());
    ASSERT_TRUE(output.getActors().size() == 1);
    ASSERT_TRUE(output.getActors() == meta.getActors());
    ASSERT_TRUE(output.getCategory() == Category::Series);
}

TEST_F(CliTest, CliTest_Upload2_Test) {
    Cli cli;
    std::string test = "upload:movie:filename:" + TEST_FILE;
    Metadata meta ("test", "horror", "dtest", {"test_act"}, Category::Movie);
    auto output = cli.process(test);
    cli.verifyUploadTest(output, meta);
    auto t = output.getTitle();
    ASSERT_TRUE(output.getTitle() == meta.getTitle());
    ASSERT_TRUE(output.getGenre() == meta.getGenre());
    ASSERT_TRUE(output.getDirector() == meta.getDirector());
    ASSERT_TRUE(output.getActors().size() == 1);
    ASSERT_TRUE(output.getActors() == meta.getActors());
    ASSERT_TRUE(output.getCategory() == Category::Movie);
}

TEST_F(CliTest, CliTest_Delete_Test) {
    Cli cli;
    std::string test = "delete:movie:title:The Proposal";
    JsonParser::getInstance().load(Category::Movie);
    auto output = cli.process(test);
    ASSERT_TRUE(output.getEvent() == Event::DELETE);
    ASSERT_TRUE("The Proposal" == output.getTitle());
    ASSERT_TRUE("Anne Fletcher" == output.getDirector());
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getErrorDesc().empty());
}

TEST_F(CliTest, CliTest_Delete2_Test) {
    Cli cli;
    std::string test = "delete:series:title:Dummy";
    JsonParser::getInstance().load(Category::Series);
    auto output = cli.process(test);
    ASSERT_TRUE(output.getEvent() == Event::DELETE);
    ASSERT_FALSE("Anne Fletcher" == output.getDirector());
    ASSERT_FALSE(output.getError() == RET::OK);
    ASSERT_FALSE(output.getErrorDesc().empty());
}

TEST_F(CliTest, CliTest_EXIT_Test)
{
    Cli cli;
    std::string line = "exit";
    auto output = cli.process(line);
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getEvent() == Event::EXIT);
}


#endif //MEDIAFW_TEST_CLI_H
