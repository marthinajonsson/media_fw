//
// Created by mjonsson on 10/29/18.
//

#ifndef MEDIAFW_TEST_OBSERVER_H
#define MEDIAFW_TEST_OBSERVER_H

#include <gtest/gtest.h>
#include <JsonParser.h>
#include <Client.h>
#include <ifc/Subject.h>
#include <gmock/gmock-generated-function-mockers.h>
#include <functional>  // for std::function and std::bind
#include <iostream>

void foo(int i)
{
    std::cout << "foo( " <<  i << " )\n";
}

void bar() {
    std::cout << "bar()\n";
}

class ObserverTest : public ::testing::Test
{
protected:
    std::map<std::string, std::vector<std::string>> m_loadedMovieMap;
    std::map<std::string, std::vector<std::string>> m_loadedSeriesMap;
    Client* client;

    void SetUp() override {
        JsonParser::getInstance().load();
        m_loadedMovieMap = JsonParser::getInstance().getMovieParsed();
        m_loadedSeriesMap = JsonParser::getInstance().getSeriesParsed();
    }

    void TearDown() override {
        JsonParser::getInstance().clearMap();
    }
};

class MockObserver : public Observer {
public:

    MockObserver() = default;
    ~MockObserver() = default;
    MOCK_METHOD2(update, bool(Event, std::vector<std::string>&));
};

TEST_F(ObserverTest, ObserverTest_GetDownloadNotification_Test) {
    MockObserver observer;
    std::vector<std::string> test = {"DOWNLOAD", "FILE.mp4"};
    client->registerObserver(&observer);
    EXPECT_CALL(observer, update(Event::DOWNLOAD, test)).Times(1).WillOnce(testing::Return(true));
}


#endif //MEDIAFW_TEST_OBSERVER_H
