#include "MediaHandler.h"
#include "Test_Startup.h"

#include <thread>

static std::mutex mtx;
std::condition_variable cv;
bool processed = false;

void threadCaller(MediaHandler *handler) {
    std::lock_guard<std::mutex> lock(mtx);
    handler->startThreads();
    processed = true;
    cv.notify_one();
}



int main(int argc, char **argv) {

    InputParser input(argc, argv);

    StartGoogleTest(input, argc ,argv);

    return 0;
    std::string arg = *argv;
    std::cout << "ARGV " << arg << std::endl;
    const std::string &help = input.getCmdOption("-h");
    if (!help.empty()){
        std::cout << "Run all unittests: \n" << "./mediaFW -t gtest " << std::endl;
        std::cout << "Run specific unittests: \n" << "./mediaFW -t gtest -f <val>";
        std::cout << "\t <val> => json, cli, http, db, logger" << std::endl;
        std::cout << "Run ssh mode: \n" << "./mediaFW -t ssh " << std::endl;
        std::cout << "Run normal mode :\n" << "./mediaFW" << std::endl;
    }
    const std::string &option = input.getCmdOption("-t");

    if (option.empty()){
        std::cout << "Normal mode\n" << std::endl;
        auto *handler = new MediaHandler();
        auto fut = std::async(threadCaller, handler);
        fut.get();
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{return processed;});
        std::cout << "\t" << processed << "\t" << std::endl;
        delete handler;
    }
    else if(option.find("gtest") != std::string::npos) {
        std::cout << "Test mode\n" << std::endl;
        StartGoogleTest(input, argc ,argv);
    }
    else if(option.find("ssh") != std::string::npos) {
        std::cout << "SSH mode\n" << std::endl;
    }
    return 0;

}