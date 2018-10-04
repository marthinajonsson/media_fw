//
// Created by mjonsson on 10/4/18.
//

#include "MovieDatabase.h"


void MovieDatabase::findByPattern(){}

void MovieDatabase::pushItem(DatabaseItem _item) {
    _items.push(_item);
}

DatabaseItem MovieDatabase::fetchItem(int id)  {
    if(_items.empty()){
        std::cout << "Database is empty" << std::endl;
    }
    return _items.front();
}