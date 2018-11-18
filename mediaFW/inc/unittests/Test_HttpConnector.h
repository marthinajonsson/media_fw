//
// Created by mjonsson on 11/16/18.
//

#ifndef MEDIAFW_TEST_HTTPCONNECTOR_H
#define MEDIAFW_TEST_HTTPCONNECTOR_H

#include <HttpConnector.h>
#include "gtest/gtest.h"

class HttpTest : public ::testing::Test
{
protected:

    HttpConnector p_hconn;
    Request request;
    void SetUp() override
    {
        request.setError(RET::OK);
        request.setDirector("Hitchcock");
    }

    void TearDown() override
    {

    }
};

TEST_F(HttpTest, HttpTest_Search_Test) {
    request.setEvent(Event::SEARCH);
    request.setCategory(Category::Movie);
    request.setGenre("Romance");

    std::string expected = "searchMovie --payload '{genre:Romance}' --pretty --url http://TestUser:xhfypf6C@192.168.0.107:5000";
    auto result = p_hconn.compile(request);
    ASSERT_EQ(expected, result);
};

TEST_F(HttpTest, HttpTest_Search2_Test) {
    request.setEvent(Event::SEARCH);
    request.setCategory(Category::Movie);
    request.setTitle("Proposal");

    std::string expected = "searchMovie --payload '{title:Proposal}' --pretty --url http://TestUser:xhfypf6C@192.168.0.107:5000";
    auto result = p_hconn.compile(request);
    ASSERT_TRUE(expected == result);
};

TEST_F(HttpTest, HttpTest_Download_Test) {
    request.setEvent(Event::DOWNLOAD);
    request.setCategory(Category::Series);
    request.setTitle("11.22.63");

    std::string expected = "downloadTvShow --payload '{title:11.22.63}' --pretty --url http://TestUser:xhfypf6C@192.168.0.107:5000";
    auto result = p_hconn.compile(request);
    ASSERT_TRUE(expected == result);
};

TEST_F(HttpTest, HttpTest_Delete_Test) {
    request.setEvent(Event::DELETE);
    request.setCategory(Category::Movie);
    request.setTitle("Proposal");

    std::string expected = "deleteMovie --payload '{title:Proposal}' --pretty --url http://TestUser:xhfypf6C@192.168.0.107:5000";
    auto result = p_hconn.compile(request);
    ASSERT_TRUE(expected == result);
};

TEST_F(HttpTest, HttpTest_Upload_Test) {
    request.setEvent(Event::UPLOAD);
    request.setCategory(Category::Movie);
    request.setFilename("testfile.txt");

    std::string expected = "uploadMovie --payload '{filename:testfile.txt}' --pretty --url http://TestUser:xhfypf6C@192.168.0.107:5000";
    auto result = p_hconn.compile(request);
    ASSERT_TRUE(expected == result);
};


#endif //MEDIAFW_TEST_HTTPCONNECTOR_H
