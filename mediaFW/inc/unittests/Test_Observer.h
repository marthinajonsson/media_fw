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
#include <MediaHandler.h>

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
    Client* client; // a.k.a Subject

    void SetUp() override {
        client = new Client;
        JsonParser::getInstance().load();
        m_loadedMovieMap = JsonParser::getInstance().getMovieParsed();
        m_loadedSeriesMap = JsonParser::getInstance().getSeriesParsed();
    }

    void TearDown() override {
        JsonParser::getInstance().clearMap();
        delete client;
    }
};

class MockObserver : public MediaHandler {
public:

    MockObserver() = default;
    ~MockObserver() = default;
    MOCK_METHOD2(update, bool(Event, std::vector<std::string>&));
};

TEST_F(ObserverTest, ObserverTest_GetDownloadNotification_Test) {
    MockObserver observer;
    std::vector<std::string> test = {"download", "The Proposal"};
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(Event::DOWNLOAD, test); // anropas r'tt men mediahandler disposas eft[[t vilket skiter rsig f;r update
    EXPECT_CALL(observer, update(Event::DOWNLOAD, test)).Times(1).WillOnce(testing::Return(true));

}

TEST_F(ObserverTest, ObserverTest_GetSearchotification_Test) {
    MockObserver observer;
    std::vector<std::string> test = {"search", "The Proposal"};
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(Event::SEARCH, test);
    EXPECT_CALL(observer, update(Event::SEARCH, test)).Times(1).WillOnce(testing::Return(true));
}

TEST_F(ObserverTest, ObserverTest_GetUploadNotification_Test) {
    MockObserver observer;
    std::vector<std::string> test = {"upload", "FILE.mp4"};
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(Event::UPLOAD, test);
    EXPECT_CALL(observer, update(Event::UPLOAD, test)).Times(1).WillOnce(testing::Return(true));
}


#endif //MEDIAFW_TEST_OBSERVER_H
