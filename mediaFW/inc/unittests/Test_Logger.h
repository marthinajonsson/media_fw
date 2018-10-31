//
// Created by mjonsson on 10/31/18.
//

#ifndef MEDIAFW_TEST_LOGGER_H
#define MEDIAFW_TEST_LOGGER_H

#include <StatusLogger.h>
#include "gmock/gmock.h"

TEST(LoggerTest, LoggerTest_WriteInfo__Test) {
    StatusLogger log;
    ASSERT_NO_THROW(log.TRACE(Logger::INFO, "Something happened"));
}

TEST(LoggerTest, LoggerTest_WriteWarn__Test) {
    StatusLogger log;
    ASSERT_NO_THROW(log.TRACE(Logger::WARN, "Something happened"));
}

TEST(LoggerTest, LoggerTest_WriteERR__Test) {
    StatusLogger log;
    ASSERT_NO_THROW(log.TRACE(Logger::ERR, "Something happened"));
}


TEST(LoggerTest, LoggerTest_WriteMult__Test) {
    StatusLogger log;
    ASSERT_NO_THROW(log.TRACE(Logger::WARN, "Something happened"));

    ASSERT_NO_THROW(log.TRACE(Logger::INFO, "YES"));

    ASSERT_NO_THROW(log.TRACE(Logger::ERR, "Oh noo"));
}

#endif //MEDIAFW_TEST_LOGGER_H
