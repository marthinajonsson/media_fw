//
// Created by mjonsson on 10/28/18.
//

#ifndef MEDIAFW_TEST_JSON_H
#define MEDIAFW_TEST_JSON_H

#include <JsonParser.h>
#include "gmock/gmock.h"

class JsonTest : public ::testing::Test
{
protected:
    std::map<std::string, std::vector<std::string>> m_loadedMovieMap;
    std::map<std::string, std::vector<std::string>> m_loadedSeriesMap;

    void SetUp() override {
        JsonParser::getInstance().load();
        m_loadedMovieMap = JsonParser::getInstance().getMovieParsed();
        m_loadedSeriesMap = JsonParser::getInstance().getSeriesParsed();
    }

    void TearDown() override {
        JsonParser::getInstance().clearMap();
    }
};


TEST_F(JsonTest, JsonTest_Load_Test) {
    ASSERT_TRUE(m_loadedMovieMap.size() == 2);
    ASSERT_TRUE(m_loadedSeriesMap.size() == 1);
}

TEST_F(JsonTest, JsonTest_FindMovie_Test) {
    const std::string findTitle = "The Proposal";
    const std::string findActor = "Thomas Beaudoin";
    bool found = JsonParser::getInstance().find(MOVIE,findTitle);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(MOVIE, findActor);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(MOVIE, "not_in_db");
    ASSERT_TRUE(!found);
}

TEST_F(JsonTest, JsonTest_FindSeries_Test) {
    const std::string findTitle = "11.22.63";
    const std::string findActor = "James Franco";
    bool found = JsonParser::getInstance().find(SERIES,findTitle);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(SERIES, findActor);
    ASSERT_TRUE(found);
    found = JsonParser::getInstance().find(SERIES, "not_in_db");
    ASSERT_TRUE(!found);
}

#endif //MEDIAFW_TEST_JSON_H
