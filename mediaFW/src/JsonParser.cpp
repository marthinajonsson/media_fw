//
// Created by mjonsson on 10/12/18.
//
//

#include "JsonParser.h"
#include "json/json.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>



void JsonParser::parser()
{
    Json::Value root;
    std::string actors;
    std::string title;
    std::ifstream db_file("../data/db.json", std::ifstream::binary);
    db_file >> root;
    _map.clear();

    for (int i = 0; root["items"]["Movies"].isValidIndex(i) == true; i++) {
        _parsed.clear();
        title = root["items"]["Movies"][i]["title"].asString();
        std::string genre = root["items"]["Movies"][i]["genre"].asString();
        std::string director = root["items"]["Movies"][i]["director"].asString();
        actors = root["items"]["Movies"][i]["actors"].asString();

        _parsed.push_back(genre);
        _parsed.push_back(director);

        std::stringstream ss(actors);
        std::string str;
        while (ss >> str)
        {
            _parsed.push_back(str);
            if (ss.peek() == ',')
                ss.ignore();
        }
        _map[title] = _parsed;
    }

}

void JsonParser::updateDB () {

}
