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

TEST(DatabaseTest, DatabaseTest_BaseTest__Test) {
    MovieDatabase db;
    db.getNumberOfItem();
    DatabaseItem item = db.fetchItem("The Proposal");
    ASSERT_EQ(item.getTitle(), "The Proposal");
}

TEST(DatabaseTest, MovieDatabaseTest_Startup_Test) {
    MovieDatabase db;
    long numberOfItems = db.getNumberOfItem();
    ASSERT_TRUE(numberOfItems == 3);
}

TEST(DatabaseTest, MovieDatabaseTest_FetchAndPush_Test) {
    MovieDatabase db;
    Category cat = Category::Movie;
    Request req(Event::UPLOAD);
    std::string t = "aTitle";
    std::string g = "horror";
    std::string d = "dir";
    req.setProperties(t, g, d);
    req.setActors({"actor1", "actor2"});
    req.setCategory(cat);
    DatabaseItem newItem;
    newItem.setFeature(req);

    long firstNum = db.getNumberOfItem();
    db.pushItem(newItem);
    long postPushNum = db.getNumberOfItem();
    ASSERT_TRUE((firstNum+1) == postPushNum);

    DatabaseItem anotherItem;
    anotherItem = db.fetchItem("aTitle");
    ASSERT_EQ(anotherItem.getTitle(), newItem.getTitle());
    ASSERT_EQ(anotherItem.getGenre(), newItem.getGenre());
    ASSERT_EQ(anotherItem.getDirector(), newItem.getDirector());
    ASSERT_EQ(anotherItem.getActors(), newItem.getActors());
}

TEST(DatabaseTest, MovieDatabaseTest_PushAndPurgeItems_Test) {
    MovieDatabase db;
    Category cat = Category::Movie;
    Request req(Event::UPLOAD);
    req.setActors({"actor1", "actor2"});
    req.setProperties("aTitle", "horror", "Spielberg");
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
