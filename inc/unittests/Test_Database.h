//
// Created by mjonsson on 10/15/18.
//

#ifndef MEDIAFW_TEST_DATABASE_H
#define MEDIAFW_TEST_DATABASE_H

//#include "Mocks.h"
//#include "Fixtures.h"

#include "gtest/gtest.h"
#include "Database.h"
#include "MovieDatabase.h"

class DatabaseTest : public ::testing::Test
{
protected:

    std::string t = "aTitle";
    std::string g = "horror";
    std::string d = "Spielberg";
    std::vector<std::string> vec = {"act1", "act2"};

    void SetUp() override
    {
        //
    }

    void TearDown() override
    {
        //
    }
};


TEST_F(DatabaseTest, DatabaseTest_BaseTest__Test) {
    MovieDatabase db;
    db.getNumberOfItem();
    DatabaseItem item = db.fetchItem("The Proposal");
    ASSERT_TRUE(item.getTitle() == "The Proposal");
}

TEST_F(DatabaseTest, MovieDatabaseTest_Startup_Test) {
    MovieDatabase db;
    long numberOfItems = db.getNumberOfItem();
    ASSERT_TRUE(numberOfItems == 3);
}

TEST_F(DatabaseTest, MovieDatabaseTest_FetchAndPush_Test) {
    MovieDatabase db;
    Category cat = Category::Movie;
    Request req(Event::UPLOAD);
    req.set(TITLE, t);
    req.set(GENRE, g);
    req.set(DIRECTOR, d);
    req.setActors(vec);
    req.setCategory(cat);
    DatabaseItem newItem;
    newItem.setFeature(req);

    long firstNum = db.getNumberOfItem();
    db.pushItem(newItem);
    long postPushNum = db.getNumberOfItem();
    ASSERT_TRUE((firstNum+1) == postPushNum);

    DatabaseItem anotherItem;
    anotherItem = db.fetchItem(t);
    ASSERT_TRUE(anotherItem.getTitle() == newItem.getTitle());
    ASSERT_TRUE(anotherItem.getGenre() == newItem.getGenre());
    ASSERT_TRUE(anotherItem.getDirector() == newItem.getDirector());
    ASSERT_TRUE(anotherItem.getActors() == newItem.getActors());
}

TEST_F(DatabaseTest, MovieDatabaseTest_PushAndPurgeItems_Test) {
    MovieDatabase db;
    Category cat = Category::Movie;
    Request req(Event::UPLOAD);
    req.setActors(vec);
    req.set(TITLE, t);
    req.set(GENRE, g);
    req.set(DIRECTOR, d);
    req.setCategory(cat);
    DatabaseItem newItem;
    newItem.setFeature(req);

    long num = db.getNumberOfItem();
    db.pushItem(newItem);
    long num2 = db.getNumberOfItem();
    db.purgeItem(newItem);
    long num3 = db.getNumberOfItem();
    ASSERT_TRUE(num == num3);
    ASSERT_TRUE(num3 == (num2 - 1));
}
#endif //MEDIAFW_TEST_DATABASE_H
