
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

    std::string args = *argv;

    if(argc < 3){
        auto *handler = new MediaHandler();
        auto fut = std::async(threadCaller, handler);
        fut.get();
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{return processed;});
        std::cout << "\t" << processed << "\t" << std::endl;
        delete handler;
    }
    else {
        std::cout << "Test mode\n" << std::endl;
        StartGoogleTest(argc ,argv);
    }
    return 0;
}

