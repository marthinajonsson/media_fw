
#include "MediaHandler.h"
#include "Test_Startup.h"

int main(int argc, char **argv) {

    if(argc > 1) {
        StartGoogleTest(argc ,argv);
    }
    else {
        MediaHandler mediaHandler;
    }
}

