
#include "MediaHandler.h"
#include "Test_Startup.h"
#include <thread>
static std::mutex mtx;
std::condition_variable cv;
bool processed = false;

void threadCaller(MediaHandler *handler) {
    std::lock_guard<std::mutex> lock(mtx);
    handler->startCliThread();
    processed = true;
    cv.notify_one();
}

int main(int argc, char **argv) {

    std::string args = *argv;
    Category category = Category::Movie;

    if(argc < 3){
        std::cout << "Normal mode: " << category << "\n" << std::endl;
        if(args.find("series")) {
            category = Category::Series;
        }

        auto *handler = new MediaHandler(category);
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
}

