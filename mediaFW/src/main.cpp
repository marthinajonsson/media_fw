#include <iostream>
#include "../inc/Connection.h"
#include "../inc/Cli.h"
#include "../inc/Database.h"


int main() {
    std::cout << "Hello, Worlds!" << std::endl;
    Database db;

    DatabaseItem item {{"Marthina"}, "title", "comedy", "hitchcock"};
    db.pushItem(item);

    DatabaseItem item2(item);
    item2 = db.fetchItem(1);
//
//    Connection mm;
//    Cli cl;

    return 0;
}