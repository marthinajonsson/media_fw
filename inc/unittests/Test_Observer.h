//
// Created by mjonsson on 10/29/18.
//

#ifndef MEDIAFW_TEST_OBSERVER_H
#define MEDIAFW_TEST_OBSERVER_H


#include <MediaHandler.h>
#include <Client.h>
#include "Gmocker.h"
#include <gtest/gtest.h>

inline bool operator==(const Request& lhs, const Request& rhs)
{
    return true;
}

std::string t = "The Proposal";

TEST(ObserverTest, ObserverTest_GetSearchNotification_Test) {
    MockObserver observer;
    MockObserver::Mock::VerifyAndClearExpectations(&observer);
    Request request;
    request.setEvent(Event::SEARCH);
    request.set(TITLE, t);

    observer.p_client->registerObserver(&observer);
    std::size_t numObservers = observer.p_client->observers.size();
    ASSERT_TRUE(numObservers == 2); // base class + mock class

    EXPECT_CALL(observer, update(request)).Times(testing::AtLeast(1));
    observer.p_client->notifyObservers(request);
}

TEST(ObserverTest, ObserverTest_GetDeleteNotification_Test) {
    MockObserver observer;
    Request request(Event::DELETE);
    request.set(TITLE, t);

    observer.p_client->registerObserver(&observer);
    ASSERT_TRUE(observer.p_client->observers.size() == 2);
    EXPECT_CALL(observer, update(request)).Times(testing::AtLeast(1));
    observer.p_client->notifyObservers(request);
}

TEST(ObserverTest, ObserverTest_GetDownloadNotification_Test) {
    MockObserver observer;
    Request request(Event::DOWNLOAD);
    request.set(TITLE, t);

    observer.p_client->registerObserver(&observer);
    ASSERT_TRUE(observer.p_client->observers.size() == 2);
    EXPECT_CALL(observer, update(request)).Times(testing::AtLeast(1));
    observer.p_client->notifyObservers(request);

}


#endif //MEDIAFW_TEST_OBSERVER_H
