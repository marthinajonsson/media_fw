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
    auto output = cli.process(test);
    auto title = output.getMetadata()->m_title;
    auto e = output.getEvent();
    auto err = output.getError();
    auto errStr = output.getErrorDesc();
    ASSERT_TRUE(e == Event::DOWNLOAD);
    ASSERT_TRUE(title == "The Proposal");
    ASSERT_TRUE(err == RET::OK);
    ASSERT_TRUE(errStr.empty());
}

TEST_F(CliTest, CliTest_Download2_Test) {
    std::string test = "download:movie:actor:Thomas Beaudoin";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    auto output = cli.process(test);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_FALSE(output.getMetadata()->m_title == "The Spirit of Christmas");
    auto act = output.getMetadata()->m_actors;
    auto it = std::find(act.begin(), act.end(), "Thomas Beaudoin");
    bool found = it != act.end();
    ASSERT_FALSE(found);
    ASSERT_TRUE(output.getError() == RET::ERROR);
}

TEST_F(CliTest, CliTest_Download3__Test) {
    std::string test = "download:movie:genre:Romance";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    auto output = cli.process(test);
    ASSERT_TRUE(output.getError() == RET::ERROR);
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getMultipleResult().empty());
}

TEST_F(CliTest, CliTest_Download4__Test) {
    std::string test = "download:series:title:11.22.63";
    JsonParser::getInstance().load(Category::Series);
    Cli cli;
    auto output = cli.process(test);
    auto metadata = output.getMetadata();
    ASSERT_TRUE(output.getEvent() == Event::DOWNLOAD);
    ASSERT_TRUE(output.getMultipleResult().empty());
    ASSERT_TRUE(metadata->m_title == "11.22.63");
    ASSERT_FALSE(metadata->m_genre == "Mystery");
    ASSERT_FALSE(metadata->m_director == "James Franco");
    ASSERT_TRUE(metadata->m_actors.size() == 1);
}


TEST_F(CliTest, CliTest_Search_Test) {
    std::string test = "search:movie:genre:Romance";
    JsonParser::getInstance().load(Category::Movie);
    Cli cli;
    auto output = cli.process(test);
    auto items = output.getMultipleResult();

    ASSERT_TRUE(items.size() == 2);
    for(auto i : items) {
        auto g = i.second.m_genre;
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
    Metadata meta;
    meta.m_title = "test";
    meta.m_genre = "horror";
    meta.m_director = "dtest";
    meta.m_actors = {"test_act"};
    meta.m_category = Category::Series;
    JsonParser::getInstance().load(Category::Series);
    auto output = cli.process(test);
    cli.verifyUploadTest(output, meta);
    auto outputMeta = output.getMetadata();
    ASSERT_TRUE(outputMeta->m_title == meta.m_title);
    ASSERT_TRUE(outputMeta->m_genre == meta.m_genre);
    ASSERT_TRUE(outputMeta->m_director == meta.m_director);
    ASSERT_TRUE(outputMeta->m_actors.size() == 1);
    ASSERT_TRUE(outputMeta->m_actors == meta.m_actors);
    ASSERT_TRUE(outputMeta->m_category == Category::Series);
}

TEST_F(CliTest, CliTest_Upload2_Test) {
    Cli cli;
    std::string test = "upload:movie:filename:" + TEST_FILE;
    Metadata meta;
    meta.m_title = "test";
    meta.m_genre = "horror";
    meta.m_director = "dtest";
    meta.m_actors = {"test_act"};
    meta.m_category = Category::Movie;
    auto output = cli.process(test);
    cli.verifyUploadTest(output, meta);

    auto outputMeta = output.getMetadata();
    ASSERT_TRUE(outputMeta->m_title == meta.m_title);
    ASSERT_TRUE(outputMeta->m_genre == meta.m_genre);
    ASSERT_TRUE(outputMeta->m_director == meta.m_director);
    ASSERT_TRUE(outputMeta->m_actors.size() == 1);
    ASSERT_TRUE(outputMeta->m_actors == meta.m_actors);
    ASSERT_TRUE(outputMeta->m_category == Category::Movie);
}

TEST_F(CliTest, CliTest_Delete_Test) {
    Cli cli;
    std::string test = "delete:movie:title:The Proposal";
    JsonParser::getInstance().load(Category::Movie);
    auto output = cli.process(test);
    auto outputMeta = output.getMetadata();
    ASSERT_TRUE(output.getEvent() == Event::DELETE);
    ASSERT_TRUE("The Proposal" == outputMeta->m_title);
    ASSERT_FALSE("Anne Fletcher" == outputMeta->m_director);
    ASSERT_TRUE(output.getError() == RET::OK);
    ASSERT_TRUE(output.getErrorDesc().empty());
}

TEST_F(CliTest, CliTest_Delete2_Test) {
    Cli cli;
    std::string test = "delete:series:title:Dummy";
    JsonParser::getInstance().load(Category::Series);
    auto output = cli.process(test);

    auto outputMeta = output.getMetadata();
    ASSERT_TRUE(output.getEvent() == Event::DELETE);
    ASSERT_FALSE("Anne Fletcher" == outputMeta->m_director);
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
