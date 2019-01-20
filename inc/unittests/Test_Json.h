//
// Created by mjonsson on 10/28/18.
//

#ifndef MEDIAFW_TEST_JSON_H
#define MEDIAFW_TEST_JSON_H

#include "JsonParser.h"
#include "DatabaseItem.h"
#include "gtest/gtest.h"

class JsonTest : public ::testing::Test
{
protected:

    void SetUp() override
    {
        JsonParser::getInstance().clear();
    }

    void TearDown() override
    {
        std::cout << "teardown" << std::endl;
    }
};


TEST(JsonTest, JsonTest_Load_Test) {
    JsonParser::getInstance().load(Category::Movie);
    auto movies = JsonParser::getInstance().getLoaded();

    JsonParser::getInstance().load(Category::Series);
    auto series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 2);

    ASSERT_TRUE(series.size() == 1);
}

TEST(JsonTest, JsonTest_FindMovie_Test) {
    std::string findTitle = "The Proposal";
    std::string findActor = "Thomas Beaudoin";
    std::string notInDB = "not_in_db";
    std::string romance = "Romance";
    std::string dir = "David Jackson";
    Category cat = Category::Movie;
    JsonParser::getInstance().load(Category::Movie);
    bool found = JsonParser::getInstance().find(cat, findTitle);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(cat, findActor);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(cat, romance);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(cat, notInDB);
    ASSERT_FALSE(found);
    found = JsonParser::getInstance().find(cat, dir);
    ASSERT_TRUE(found);
}

TEST(JsonTest, JsonTest_FindSeries_Test) {
    std::string findTitle = "11.22.63";
    std::string findActor = "James Franco";
    std::string notInDB = "not_in_db";
    Category cat = Category::Series;
    JsonParser::getInstance().load(Category::Series);
    bool found = JsonParser::getInstance().find(cat, findTitle);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(cat, findActor);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(cat, notInDB);
    ASSERT_TRUE(!found);

    JsonParser::getInstance().clear();
}


TEST(JsonTest, JsonTest_AddRemoveMovie_Test) {
    DatabaseItem item;
    Request request(Event::UPLOAD);
    std::string t = "titleT";
    std::string g = "horror";
    std::string d = "Marthina";
    request.set(TITLE, t);
    request.set(GENRE, g);
    request.set(DIRECTOR, d);
    request.setActors({"Trazan", "Banarne"});

    item.setFeature(request);
    JsonParser::getInstance().load(Category::Movie);
    auto movies = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 2);

    JsonParser::getInstance().load(Category::Series);
    auto series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(series.size() == 1);

    JsonParser::getInstance().add(Category::Movie, item);
    JsonParser::getInstance().load(Category::Movie);
    movies = JsonParser::getInstance().getLoaded();
    JsonParser::getInstance().load(Category::Series);
    series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 3);
    ASSERT_TRUE(series.size() == 1);

    JsonParser::getInstance().remove(Category::Movie, item);
    JsonParser::getInstance().load(Category::Movie);
    movies = JsonParser::getInstance().getLoaded();
    JsonParser::getInstance().load(Category::Series);
    series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 2);
    ASSERT_TRUE(series.size() == 1);

    JsonParser::getInstance().clear();
}

TEST(JsonTest, JsonTest_AddRemoveSeries_Test) {
    DatabaseItem item;
    Request request(Event::UPLOAD);
    std::string t = "titleT";
    std::string g = "horror";
    std::string d = "Marthina";
    request.set(TITLE, t);
    request.set(GENRE, g);
    request.set(DIRECTOR, d);
    request.setActors({"Trazan", "Banarne"});

    item.setFeature(request);
    JsonParser::getInstance().load(Category::Movie);
    auto movies = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 2);

    JsonParser::getInstance().load(Category::Series);
    auto series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(series.size() == 1);
    ASSERT_TRUE(movies.size() == 2);
    ASSERT_TRUE(series.size() == 1);

    JsonParser::getInstance().add(Category::Series, item);
    JsonParser::getInstance().load(Category::Movie);
    movies = JsonParser::getInstance().getLoaded();
    JsonParser::getInstance().load(Category::Series);
    series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 2);
    ASSERT_TRUE(series.size() == 2);

    JsonParser::getInstance().remove(Category::Series, item);;
    JsonParser::getInstance().load(Category::Movie);
    movies = JsonParser::getInstance().getLoaded();
    JsonParser::getInstance().load(Category::Series);
    series = JsonParser::getInstance().getLoaded();
    ASSERT_TRUE(movies.size() == 2);
    ASSERT_TRUE(series.size() == 1);

    JsonParser::getInstance().clear();
}
#endif //MEDIAFW_TEST_JSON_H
