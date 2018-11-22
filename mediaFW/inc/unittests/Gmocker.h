//
// Created by marthina on 2018-11-18.
//

#ifndef MEDIAFW_GMOCKER_H
#define MEDIAFW_GMOCKER_H

#include <MediaHandler.h>
#include <gmock/gmock.h>

class MockObserver : public MediaHandler, public ::testing::Mock {
public:
    MockObserver() {};
    ~MockObserver() override {};

    MOCK_METHOD1(update, int(Request& req));

};
#endif //MEDIAFW_GMOCKER_H
