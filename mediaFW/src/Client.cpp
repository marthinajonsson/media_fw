//
// Created by mjonsson on 10/4/18.
//

#include "Client.h"
#include "Util.h"

/*! \class Client client.h "inc/client.h"
 *  \brief Class implementing the functionality of a client.
 *
 * Receives and interpretes information from stdin and sends requests to the server.
 */


bool Client::getConnectionStatus () {
    return p_conn->getConnectionStatus();
}

bool Client::isRequestInQueue() { return  !m_requests.empty(); }

/*
 *
 *  RETREIVE CLI INPUT
 *
 */
Request Client::getCliInput(Cli* p_cli) {
    return p_cli->process();
}


/*
 *  THREADS
 *
 * */
int Client::handleCliThread()
{
    std::vector<std::string> resultVector;
    std::string choice;
    std::future<Request> fut;
    while(true)
    {
        resultVector.clear();
        fut = std::async(getCliInput, p_cli);
        auto result = fut.get();

        pushRequest(result);
        if(result.getEvent() == Event::EXIT) {
            return RET::OK;
        }


    }
}

int Client::handleRequestThread()
{
    while (true) {
        if(!m_requests.empty()) {
            auto request = popRequest();

            if(request.getEvent() == Event::EXIT) {
                return RET::OK;
            }
            request.setProgress(Progress::InProgress);
            notifyObservers(request);

            std::string result;
            std::string testcommand = "ls";
            //p_conn->sendServerRequest(testcommand, result);
            std::cout << result << std::endl;

            request.setProgress(Progress::Done);
            notifyObservers(request);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}


/*
 *
 *  POP and PUSH
 *
 */
Request Client::popRequest() {
    std::unique_lock<std::mutex>  m_lock;
    m_condVar.wait(m_lock, std::bind(&Client::isRequestInQueue, this));
    if(m_requests.empty()) {
        Request err(RET::ERROR, "No request to pop");
        return err;
    }
    if (m_requests.size() == 1) {
        m_queueEmpty = false; // it is now empty again
    }
    auto popped = m_requests.front();
    m_requests.pop();
    return popped;
}

void Client::pushRequest(const Request &m_request) {
    std::unique_lock<std::mutex> guard(m_lock);
    if(m_requests.empty()) {
        m_queueEmpty = true;
        m_condVar.notify_all();
    }
    m_requests.push(m_request);
}



/*
 *
 *  SUBJECT PATTERN
 *
 */
void Client::registerObserver(Observer *observer) {
    observers.push_back(observer);
}
void Client::removeObserver(Observer *observer) {
    auto iterator = std::find(observers.begin(), observers.end(), observer);

    if (iterator != observers.end()) { // observer found
        observers.erase(iterator); // remove the observer
    }
}
void Client::notifyObservers(Request &request) {
    for (Observer *observer : observers) { // notify all observers
        observer->update(request);
    }
}
