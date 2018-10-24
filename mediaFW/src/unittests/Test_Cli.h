//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_TEST_CLI_H
#define MEDIAFW_TEST_CLI_H
#include "gmock/gmock.h"

#include "Cli.h"


TEST(CliTest, ParseArguments) {

    Cli cli;
    std::string test = "upload test1 test2 'test test3'";
    std::vector<std::string> output;
    output = cli.process(test);
    ASSERT_TRUE(output.size() == 5);
    ASSERT_TRUE(output.front() == "upload");
}


TEST(CliTest, ParseArguments2) {

    Cli cli;
    std::string test = "download test1 test2 test.test3";
    std::vector<std::string> output;
    output = cli.process(test);
    ASSERT_TRUE(output.size() == 4);
    ASSERT_TRUE(output.front() == "download");
}

TEST(CliTest, ParseArguments3) {

    Cli cli;
    std::string test = "search test1 a.test3";
    std::vector<std::string> output;
    output = cli.process(test);
    ASSERT_TRUE(output.size() == 3);
    ASSERT_TRUE(output.front() == "search");
}

TEST(CliTest, ParseHelp) {

    Cli cli;
    std::string test = "help";
    std::vector<std::string> output;
    output = cli.process(test);
    ASSERT_TRUE(output.size() == 1);
    ASSERT_TRUE(output.front() == test);
}
#endif //MEDIAFW_TEST_CLI_H
