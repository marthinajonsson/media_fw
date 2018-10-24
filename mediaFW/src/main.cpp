
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

// TODO: divide into submodules to allow better structure and unit tests
// TODO: consider removing vector<string> and just add strings
