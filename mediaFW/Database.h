//
// Created by mjonsson on 10/3/18.
//

#ifndef MEDIAFW_DATABASE_H
#define MEDIAFW_DATABASE_H

#include <string>
#include <queue>
#include <iostream>
#include "DatabaseItem.h"

enum Pattern {
    TITLE = 4,
    ACTOR,
    GENRE = 2,
    DIRECTOR
};

class Database {
public:
    Database() {
        DatabaseItem _item;
    }
    ~Database() = default;

    void updateItem(){

    }

    DatabaseItem fetchItem(int id){
        if(_items.empty()){
            std::cout << "Database is empty" << std::endl;
        }
        return _items.front();
    }

    std::vector<DatabaseItem> fetchItems(std::string pattern, Pattern ptt){
        return {new DatabaseItem, new DatabaseItem};
    }

private:
    std::queue<DatabaseItem> _items;
};


#endif //MEDIAFW_DATABASE_H
