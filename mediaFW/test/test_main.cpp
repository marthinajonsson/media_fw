#include "Test_Database.h"
#include "Test_Cli.h"
#include "Test_Startup.h"
#include "Test_Json.h"
#include "Test_HttpConnector.h"
//#include "Test_Observer.h"
#include "Test_Logger.h"

int StartGoogleTest(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}