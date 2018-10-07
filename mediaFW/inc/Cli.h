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

    std::vector<std::string> daemon(std::string &choice);

private:
    std::vector<std::string> parseArg(std::string &input);
    std::vector<std::string> handleInput(std::string input, std::string &choice, std::vector<std::string> &args);
    void printOptions();

    enum CHOICE {
        UPLOAD = 3,
        DOWNLOAD,
        SEARCH = 1,
        NO_OPTION
    };
};

#endif //MEDIAFW_CLI_H
