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
    long numberOfItems = db->getNumberOfItem();
    std::cout << numberOfItems << std::endl;
    ASSERT_TRUE(db->getNumberOfItem() == 1);
    db->printAll();
    delete db;
}
#endif //MEDIAFW_TEST_DATABASE_H
