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

TEST(DatabaseTest, BaseDatabase) {
    Database db;
    ASSERT_ANY_THROW(db.syncDatabase());
    ASSERT_ANY_THROW(db.getNumberOfItem());
    ASSERT_ANY_THROW(db.fetchItem("TestTitle"));
}

TEST(MovieDatabaseTest, HandleStartup) {
    Database *db;
    ASSERT_NO_THROW(db = new MovieDatabase());
    db->printAll();
    long numberOfItems = db->getNumberOfItem();
    std::cout << numberOfItems << std::endl;

    ASSERT_TRUE(db->getNumberOfItem() == 2);
    delete db;
}


TEST(MovieDatabaseTest, PushAndFetch) {
    Database *db;
    ASSERT_NO_THROW(db = new MovieDatabase());

    DatabaseItem newItem {{"actor1", "actor2"}, "aTitle", "horror", "spielberg"};
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


    db->purgeItem(newItem);
    ASSERT_TRUE(db->getNumberOfItem() == firstNum);

//    const std::string emptyString{" "};
//    ASSERT_NE(db->fetchItem("aTitle"), emptyString);

    delete db;
}
#endif //MEDIAFW_TEST_DATABASE_H
