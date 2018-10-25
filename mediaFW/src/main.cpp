
#include "MediaHandler.h"
#include "Test_Startup.h"


int main(int argc, char **argv) {

    if(argc > 1) {
        std::cout << "Init test" << std::endl;
        StartGoogleTest(argc ,argv);
    }
    else {
        MediaHandler mediaHandler;
    }
}

