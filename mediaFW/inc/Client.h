//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H

#include <algorithm>
#include <queue>
#include <mutex>
#include <future>
#include <thread>
#include <functional>

#include "ifc/Subject.h"
#include "Connection.h"
#include "Cli.h"
#include "StatusLogger.h"



class Client : Subject{
public:
    Client() = default;
    ~Client() = default;

    Client(Connection *_conn, Cli* _cli) : p_conn(_conn), p_cli(_cli),  m_logger(new StatusLogger) {
        std::cout << "Client constructor" << std::endl;
    };

    int waitCliAsync();

    void handleRequest();

    bool getConnectionStatus();

    Request pop();

    void push(const Request &m_request);

    /*! \public registerObserver
     * @brief register observers for event notification
     * @implements subject interface
     * @callgraph
     * @param observer
     */
    void registerObserver(Observer *observer) override;

    /*! \public removeObserver
     * @brief remove observer for event notification
     * @implements subject interface
     * @callgraph
     * @param observer
     */
    void removeObserver(Observer *observer) override;

    /*! \public notifyObservers
     * @brief notify all observers for event
     * @implements subject interface
     * @callgraph
     * @param request to send to all observers
     */
    void notifyObservers(Request &request) override;

    std::vector<Observer *> observers;

private:

    Connection *p_conn;

    Cli *p_cli;

    StatusLogger *m_logger;

    std::queue<Request> m_requests;

    mutable std::mutex m_lock;

    std::condition_variable m_emptyQ;


    /*! \privatesection Client::getCliInput(Cli* p_cli)
     * @brief A method that waits for CLI to process incoming request. Used by std::future.
     * @param p_cli - pointer to CLI instance
     * @return - A request object
     */
    static Request getCliInput(Cli* p_cli) {
        return p_cli->process();
    }
};


#endif //MEDIAFW_CLIENT_H
