//
// Created by mjonsson on 10/28/18.
//

#ifndef MEDIAFW_TEST_JSON_H
#define MEDIAFW_TEST_JSON_H

#include <JsonParser.h>
#include "gtest/gtest.h"

class JsonTest : public ::testing::Test
{
protected:
    std::map<std::string, std::vector<std::string>> m_loadedMovieMap;
    std::map<std::string, std::vector<std::string>> m_loadedSeriesMap;

    void SetUp() override {
        Category cat = Category::Movie;
        JsonParser::getInstance().load(cat);
        cat = Category::Series;
        JsonParser::getInstance().load(cat);
        m_loadedMovieMap = JsonParser::getInstance().getMovieParsed();
        m_loadedSeriesMap = JsonParser::getInstance().getSeriesParsed();
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
    std::string romance = "romance";
    std::string dir = "David Jackson";
    bool found = JsonParser::getInstance().find(MOVIE,"title", findTitle);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(MOVIE, "actor", findActor);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(MOVIE, "genre", romance);
    ASSERT_TRUE(!found);
    found = JsonParser::getInstance().find(MOVIE, "title", notInDB);
    ASSERT_FALSE(found);
    found = JsonParser::getInstance().find(MOVIE, "director", dir);
    ASSERT_TRUE(found);
}

TEST_F(JsonTest, JsonTest_FindSeries_Test) {
    std::string findTitle = "11.22.63";
    std::string findActor = "James Franco";
    std::string notInDB = "not_in_db";
    bool found = JsonParser::getInstance().find(SERIES,"title", findTitle);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(SERIES, "actor", findActor);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(SERIES, "genre" ,notInDB);
    ASSERT_TRUE(!found);
}

#endif //MEDIAFW_TEST_JSON_H
