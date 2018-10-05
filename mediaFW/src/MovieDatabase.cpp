//
// Created by mjonsson on 10/4/18.
//

#include "../inc/MovieDatabase.h"


std::vector<std::string> MovieDatabase::findByPattern() {

    return {""};
}

void MovieDatabase::pushItem(DatabaseItem _item) {
    _items.push(_item);
}

int MovieDatabase::getNumberOfItem() {

    // return number of items of given pattern
}

DatabaseItem MovieDatabase::fetchItem(int id)  {
    if(_items.empty()){
        std::cout << "Database is empty" << std::endl;
    }
    return _items.front();
}