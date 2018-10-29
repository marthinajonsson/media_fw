
#include "MediaHandler.h"
#include "Test_Startup.h"
#include <future>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ready;

MediaHandler::Status wait(MediaHandler handler) {
    return handler.
}

void handler(std::string category) {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{return ready;});

    MediaHandler handler(category);
    auto fut = std::async(wait, &handler);
    auto result = fut.get();
    if(result != 0) {
        std::cerr << "Ending due to abnormal state" << std::endl;
    }
    else {
        std::cout << "Ending normally" << std::endl;
    }
    lk.unlock();
    cv.notify_one();
}
int main(int argc, char **argv) {

    std::string args = *argv;
    std::string category = "movie";

    if(args.find("--mode")){
        std::cout << "Normal mode: " << category << "\n" << std::endl;
        if(args.find("series")) {
            category = "series";
        }

        std::thread worker(handler);
        {
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk, []{return true;});
        }
        worker.join();
    }
    else {
        std::cout << "Test mode\n" << std::endl;
        StartGoogleTest(argc ,argv);
    }
}

