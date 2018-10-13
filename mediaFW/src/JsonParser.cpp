//
// Created by mjonsson on 10/12/18.
//
//#include <json/value.h>
#include <fstream>
#include <iostream>
#include "JsonParser.h"
#include "json/json.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

/*
 *
 */

void JsonParser::parser()
{
    Json::Value root;
    std::string actors;
    std::ifstream db_file("../data/db.json", std::ifstream::binary);
    db_file >> root;
    _map.clear();

    for (int i = 0; root["items"]["Movies"].isValidIndex(i) == true; i++) {
        _parsed.clear();
        std::string title = root["items"]["Movies"][i]["title"].asString();
        std::string genre = root["items"]["Movies"][i]["genre"].asString();
        std::string director = root["items"]["Movies"][i]["director"].asString();
        actors = root["items"]["Movies"][i]["actors"].asString();

        _parsed.push_back(genre);
        _parsed.push_back(director);
        std::cout << "parser" << title << " " << genre << " " << director << std::endl;
        _map[title] = _parsed;
    }

    std::stringstream ss(actors);
    std::string str;
    while (ss >> str)
    {
        //std::cout << "act " << str << std::endl;
        _parsed.push_back(str);
        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.ignore();
    }
}