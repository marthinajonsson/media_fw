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

bool Client::getConnectionStatus () { return p_conn->getConnectionStatus(); }

bool QueueEmpty;

int Client::waitCliAsync()
{
    std::vector<std::string> resultVector;
    std::string choice;
    std::future<Request> fut;
    while(true)
    {
        resultVector.clear();
        fut = std::async(getCliInput, p_cli);
        auto result = fut.get();

        if(result.getEvent() == Event::EXIT) {
            return RET::OK;
        }

        std::unique_lock<std::mutex> guard(m_lock);
        push(result);
    }
}

void Client::handleRequest()
{
    std::unique_lock<std::mutex> guard(m_lock);
    m_emptyQ.wait(m_lock,[]{return QueueEmpty;});
    auto request = pop();
    request.setProgress(Progress::InProgress);
    notifyObservers(request);

    std::string result;
    std::string testcommand = "ls";
    //p_conn->sendServerRequest(testcommand, result);
    std::cout << result << std::endl;

    request.setProgress(Progress::Done);
    notifyObservers(request);
}


/*
 * Overriden methods implementing subject pattern
 *
 * */
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


/*! \addtogroup QueueRequestOp
 *! \callgraph
 * @param m_request
 */
void Client::push(const Request &m_request) {
    if(m_requests.empty()) {
        QueueEmpty = true;
        m_emptyQ.notify_one();
    }
    m_requests.push(m_request);
}

/*! \publicsection
 * @brief Pop a queueing request if available.
 * Used by the same thread waiting to be notified if any requests are available
 * @return request object that is next to be processed.
 */
Request Client::pop() {
    if(m_requests.empty()) {
        Request err(RET::ERROR, "No request to pop");
        return err;
    }
    if (m_requests.size() == 1) {
        QueueEmpty = false;
    }
    auto popped = m_requests.front();
    m_requests.pop();
    return popped;
}