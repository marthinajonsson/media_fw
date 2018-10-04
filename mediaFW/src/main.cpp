#include <iostream>
#include "Connection.h"
#include "Cli.h"
#include "Database.h"


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