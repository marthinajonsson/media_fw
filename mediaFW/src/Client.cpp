//
// Created by mjonsson on 10/4/18.
//
#include <future>
#include <thread>
#include "Client.h"
#include "Util.h"

/*! \class Client client.h "inc/client.h"
 *  \brief Class implementing the functionality of a client.
 *
 * Receives and interpretes information from stdin and sends requests to the server.
 */

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

        if(result.m_event == Event::EXIT) {
            return RET::OK;
        }

        handleRequest(result);
    }
    return RET::ERROR;
}

void Client::handleRequest(Request &request)
{
    notifyObservers(request);
    std::string result;
    std::string testcommand = "ls";
    p_conn->sendServerRequest(testcommand, result);
    std::cout << result << std::endl;
    //TODO: update JSON after UPLOAD or DELETE
}
