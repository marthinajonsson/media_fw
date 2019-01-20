//
// Created by mjonsson on 11/28/18.
//

#ifndef MEDIAFW_TEST_LARGERSCOPE_H
#define MEDIAFW_TEST_LARGERSCOPE_H
#include <string>

#include "Request.h"
#include "Gmocker.h"
#include "Cli.h"
#include "Client.h"
#include "MediaHandler.h"
#include "JsonParser.h"
#include "gtest/gtest.h"

class LargeTest : public ::testing::Test
{
protected:

    std::string test = "download:movie:title:The Proposal";
    std::string test2 = "search:movie:genre:Romance";
    std::string title = "The Proposal";
    std::string genre = "Romance";
    Category cat = Category::Movie;
    Cli* p_cli;
    Client* p_client;
    Database* p_database;
    void SetUp() override
    {
    }

    void TearDown() override
    {

    }
};

//inline bool operator==(const Request& lhs, const Request& rhs)
//{
//    return true;
//}

TEST_F(LargeTest, CliRequestTest_Test) {

    p_cli = new Cli();
    p_client = new Client(new Connection, p_cli);
    p_database = new MovieDatabase(p_client);


    JsonParser::getInstance().load(Category::Movie);
    auto map = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(map.size() == 2);

    auto foundG = JsonParser::getInstance().find(cat, genre);
    auto foundT = JsonParser::getInstance().find(cat, title);
    ASSERT_TRUE(foundG == foundT);
    ASSERT_TRUE(foundG);

    auto num = p_database->getNumberOfItem();
    auto request = p_cli->process(test2);

    p_client->notifyObservers(request);

    delete p_cli;
    delete p_client;
    delete p_database;
}

#endif //MEDIAFW_TEST_LARGERSCOPE_H
