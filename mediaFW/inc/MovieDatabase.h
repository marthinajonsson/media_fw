//
// Created by mjonsson on 10/4/18.
//

/*
 *  The purpose of this module is to work as an interface and help the client perform database actions
 * */

#ifndef MEDIAFW_MOVIEDATABASE_H
#define MEDIAFW_MOVIEDATABASE_H


#include "Database.h"

class MovieDatabase : public Database {
public:

    std::vector<std::string> findByPattern();
    void pushItem(DatabaseItem _item) override;
    DatabaseItem fetchItem(int id) override;
    int getNumberOfItem() override;

private:



};


#endif //MEDIAFW_MOVIEDATABASE_H
