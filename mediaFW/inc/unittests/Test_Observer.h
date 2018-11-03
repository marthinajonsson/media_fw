//
// Created by mjonsson on 10/29/18.
//

#ifndef MEDIAFW_TEST_OBSERVER_H
#define MEDIAFW_TEST_OBSERVER_H

#include <gtest/gtest.h>
#include <JsonParser.h>
#include <Client.h>
#include <ifc/Subject.h>
//#include <gmock/gmock-generated-function-mockers.h>
#include "gtest/gtest.h"
//#include "gmock/gmock-generated-function-mockers.h"
#include <functional>  // for std::function and std::bind
#include <iostream>
#include <MediaHandler.h>


class ObserverTest : public ::testing::Test
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
        JsonParser::getInstance().clear();
    }
};

class MockObserver : public MediaHandler {
public:

    MockObserver() = default;
    ~MockObserver() = default;
    MOCK_METHOD1(update, int(Request &));
};

TEST_F(ObserverTest, ObserverTest_GetDownloadNotification_Test) {
    MockObserver observer;
    Request request(Event::DOWNLOAD);
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(request);
    EXPECT_CALL(observer, update(request)).Times(1).WillOnce(testing::Return(true));

}

TEST_F(ObserverTest, ObserverTest_GetSearchotification_Test) {
    MockObserver observer;
    Request request(Event::SEARCH);
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(request);
    EXPECT_CALL(observer, update(request)).Times(1).WillOnce(testing::Return(true));
}

TEST_F(ObserverTest, ObserverTest_GetUploadNotification_Test) {
    MockObserver observer;
    Request request(Event::UPLOAD);
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(request);
    EXPECT_CALL(observer, update(request)).Times(1).WillOnce(testing::Return(true));
}


#endif //MEDIAFW_TEST_OBSERVER_H
