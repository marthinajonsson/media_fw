//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CLI_H
#define MEDIAFW_CLI_H

#include <iostream>

class Cli
{
public:
    Cli() {
        daemon();
    };
    ~Cli() = default;
private:

    void daemon();
    void process(const std::string &input);
};

#endif //MEDIAFW_CLI_H
