//
// Created by mjonsson on 10/29/18.
//

#ifndef MEDIAFW_TEST_OBSERVER_H
#define MEDIAFW_TEST_OBSERVER_H


#include <MediaHandler.h>
#include <Client.h>
#include "Gmocker.h"
#include <gtest/gtest.h>

TEST(ObserverTest, ObserverTest_GetSearchNotification_Test) {
    MockObserver observer;
    MockObserver::Mock::VerifyAndClearExpectations(&observer);
    Request request;
    request.setEvent(Event::SEARCH);
    request.setTitle("The Proposal");
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(request);
   // EXPECT_CALL(observer, update(request)).Times(1).WillOnce(testing::Return(0));

}

TEST(ObserverTest, ObserverTest_GetDeleteNotification_Test) {
    MockObserver observer;
    Request request(Event::DELETE);
    request.setTitle("The Proposal");
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(request);
    //EXPECT_CALL(observer, update(request)).Times(1).WillOnce(testing::Return(0));
}

TEST(ObserverTest, ObserverTest_GetDownloadNotification_Test) {
    MockObserver observer;
    Request request(Event::DOWNLOAD);
    request.setTitle("The Proposal");
    Client cl;
    cl.registerObserver(&observer);
    ASSERT_TRUE(cl.observers.size() == 1);
    cl.notifyObservers(request);
  //  EXPECT_CALL(observer, update(request)).Times(1).WillOnce(testing::Return(0));
}


#endif //MEDIAFW_TEST_OBSERVER_H
