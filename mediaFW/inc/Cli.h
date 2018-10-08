//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CLI_H
#define MEDIAFW_CLI_H

#include <string>
#include <vector>

class Cli
{
public:
    Cli() = default;
    ~Cli() = default;

    std::vector<std::string> daemon();

private:
    std::vector<std::string> parseArg(std::string &input);
    std::vector<std::string> handleInput(std::string input, std::vector<std::string> &args);
    void printOptions();
};

#endif //MEDIAFW_CLI_H
