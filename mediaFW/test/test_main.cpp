#include "Test_Database.h"
#include "Test_Cli.h"
#include "Test_Startup.h"
#include "Test_Json.h"
#include "Test_HttpConnector.h"
#include "Test_Observer.h"
#include "Test_Logger.h"
#include "InputParser.h"

int StartGoogleTest(InputParser &input, int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);

   ::testing::GTEST_FLAG(filter) = "JsonTest*";
    const std::string &option = input.getCmdOption("-f");
    if(option.find("json") != std::string::npos) {
        ::testing::GTEST_FLAG(filter) = "JsonTest*";
    }else  if(option.find("cli") != std::string::npos) {
        ::testing::GTEST_FLAG(filter) = "CliTest*";
    }
    else  if(option.find("db") != std::string::npos) {
        ::testing::GTEST_FLAG(filter) = "DatabaseTest*";
    }
    else  if(option.find("http") != std::string::npos) {
        ::testing::GTEST_FLAG(filter) = "HttpTest*";
    }
    else  if(option.find("logger") != std::string::npos) {
        ::testing::GTEST_FLAG(filter) = "LoggerTest*";
    }
    return RUN_ALL_TESTS();
}