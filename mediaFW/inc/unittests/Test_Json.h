//
// Created by mjonsson on 10/28/18.
//

#ifndef MEDIAFW_TEST_JSON_H
#define MEDIAFW_TEST_JSON_H

#include <JsonParser.h>
#include "DatabaseItem.h"
#include "gtest/gtest.h"

class JsonTest : public ::testing::Test
{
protected:
    std::map<std::string, metadata> m_loadedMovieMap;
    std::map<std::string, metadata> m_loadedSeriesMap;

    void SetUp() override {
        JsonParser::getInstance().load(Category::Movie);
        m_loadedMovieMap = JsonParser::getInstance().getLatestResult();

        JsonParser::getInstance().load(Category::Series);
        m_loadedSeriesMap = JsonParser::getInstance().getLatestResult();
    }

    void TearDown() override {
        JsonParser::getInstance().clear();
    }
};

/*
 *  All work
 */

TEST_F(JsonTest, JsonTest_Load_Test) {
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);
}

TEST_F(JsonTest, JsonTest_FindMovie_Test) {
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

TEST_F(JsonTest, JsonTest_FindSeries_Test) {
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
}

TEST_F(JsonTest, JsonTest_AddRemoveMovie_Test) {
    DatabaseItem item;
    Request request(Event::UPLOAD);
    request.setTitle("titleT");
    request.setGenre("horror");
    request.setDirector("Marthina");
    request.setActors({"Trazan", "Banarne"});

    item.setFeature(request);
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);

    JsonParser::getInstance().add(Category::Movie, item);
    JsonParser::getInstance().load(Category::Movie);
    m_loadedMovieMap = JsonParser::getInstance().getLatestResult();
    JsonParser::getInstance().load(Category::Series);
    m_loadedSeriesMap = JsonParser::getInstance().getLatestResult();
    ASSERT_TRUE(m_loadedMovieMap.size() == 3);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);

    JsonParser::getInstance().remove(Category::Movie, item);
    JsonParser::getInstance().load(Category::Movie);
    m_loadedMovieMap = JsonParser::getInstance().getLatestResult();
    JsonParser::getInstance().load(Category::Series);
    m_loadedSeriesMap = JsonParser::getInstance().getLatestResult();
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);
}

TEST_F(JsonTest, JsonTest_AddRemoveSeries_Test) {
    DatabaseItem item;
    Request request(Event::UPLOAD);
    request.setTitle("titleT");
    request.setGenre("horror");
    request.setDirector("Marthina");
    request.setActors({"Trazan", "Banarne"});

    item.setFeature(request);
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);

    JsonParser::getInstance().add(Category::Series, item);
    JsonParser::getInstance().load(Category::Movie);
    m_loadedMovieMap = JsonParser::getInstance().getLatestResult();
    JsonParser::getInstance().load(Category::Series);
    m_loadedSeriesMap = JsonParser::getInstance().getLatestResult();
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 2);

    JsonParser::getInstance().remove(Category::Series, item);;
    JsonParser::getInstance().load(Category::Movie);
    m_loadedMovieMap = JsonParser::getInstance().getLatestResult();
    JsonParser::getInstance().load(Category::Series);
    m_loadedSeriesMap = JsonParser::getInstance().getLatestResult();
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);
}
#endif //MEDIAFW_TEST_JSON_H
