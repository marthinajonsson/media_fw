//
// Created by mjonsson on 10/24/18.
//

#ifndef MEDIAFW_TEST_CLI_H
#define MEDIAFW_TEST_CLI_H

#include <Cli.h>
#include "gmock/gmock.h"

TEST(CliTest, ParseArguments) {

    Cli cli;
    std::string test = "upload test1 test2 test.test3";
    std::vector<std::string> output;
    output = cli.process(test);
    ASSERT_TRUE(output.size() == 5);
}

#endif //MEDIAFW_TEST_CLI_H
