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
    Cli() {
        daemon();
    };
    ~Cli() = default;

    void start();
private:
    std::vector<std::string> parseArg(std::string &input);
    void handleInput(std::string input, std::string &choice, std::vector<std::string> &args);
    void daemon();
    void printOptions();

    enum CHOICE {
        UPLOAD = 3,
        DOWNLOAD,
        SEARCH = 1,
        NO_OPTION
    };
};

#endif //MEDIAFW_CLI_H
