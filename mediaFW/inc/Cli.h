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

    virtual std::vector<std::string> process();

private:
    std::vector<std::string> parseArg(std::string &input);
    void printOptions();
};

#endif //MEDIAFW_CLI_H
