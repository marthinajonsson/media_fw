//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_MOVIEDATABASE_H
#define MEDIAFW_MOVIEDATABASE_H


#include "Database.h"

class MovieDatabase : Database {
public:

    void findByPattern();
    void pushItem(DatabaseItem _item) override;
    DatabaseItem fetchItem(int id) override;

private:



};


#endif //MEDIAFW_MOVIEDATABASE_H
