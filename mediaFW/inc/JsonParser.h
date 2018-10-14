//
// Created by mjonsson on 10/12/18.
//

#ifndef MEDIAFW_JSONPARSER_H
#define MEDIAFW_JSONPARSER_H

#include <iostream>
#include <vector>
#include <map>

class JsonParser {
public:
    JsonParser() = default;
    ~JsonParser() = default;

    void parser();
    void updateDB();
    std::map<std::string, std::vector<std::string>> getParsed() { return  _map; }

private:
    std::vector<std::string> _parsed;
    std::map<std::string, std::vector<std::string>> _map;
};


#endif //MEDIAFW_JSONPARSER_H
