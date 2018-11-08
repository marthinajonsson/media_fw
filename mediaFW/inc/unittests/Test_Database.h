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

TEST(DatabaseTest, DatabaseTest_BaseClass__Test) {
    Database db;
    db.syncLocalDatabase();
    db.getNumberOfItem();
    DatabaseItem item = db.fetchItem("The Proposal");
    ASSERT_EQ(item.getTitle(), "The Proposal");
}

TEST(MovieDatabaseTest, MovieDatabaseTest_Startup_Test) {
    Database *db;
    db = new MovieDatabase();
    db->printAll();
    long numberOfItems = db->getNumberOfItem();
    ASSERT_TRUE(numberOfItems == 2);
    delete db;
}

TEST(MovieDatabaseTest, MovieDatabaseTest_FetchAndPush_Test) {
    Database *db;
    db = new MovieDatabase();
    Category cat = Category::Movie;
    Request req(Event::UPLOAD);
    req.setActors({"actor1", "actor2"});
    req.setTitle("aTitle");
    req.setGenre("horror");
    req.setDirector("spielberg");
    req.setCategory(cat);
    DatabaseItem newItem;
    newItem.setFeature(req);

    long firstNum = db->getNumberOfItem();
    db->pushItem(newItem);
    long postPushNum = db->getNumberOfItem();
    ASSERT_TRUE((firstNum+1) == postPushNum);

    DatabaseItem anotherItem;
    anotherItem = db->fetchItem("aTitle");
    ASSERT_EQ(anotherItem.getTitle(), newItem.getTitle());
    ASSERT_EQ(anotherItem.getGenre(), newItem.getGenre());
    ASSERT_EQ(anotherItem.getDirector(), newItem.getDirector());
    ASSERT_EQ(anotherItem.getActors(), newItem.getActors());

    delete db;
}

TEST(MovieDatabaseTest, AddItems) {

}
#endif //MEDIAFW_TEST_DATABASE_H
