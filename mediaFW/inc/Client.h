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

using namespace std::placeholders;

class Client : Subject {

public:

    Client() {};
    ~Client()  {
        std::cout << "client deconstructor" << std::endl;
    };

    Client(Connection *_conn, Cli* _cli) : p_conn(_conn), p_cli(_cli),  m_logger(new StatusLogger), m_queueEmpty(false) {};


    bool getConnectionStatus();

    bool isRequestInQueue ();

    /*! \public handleRequestThread
     * @brief when available pop requests from queue and process them.
     * @callgraph
     * @return RET::OK when CLI is exiting
     */
    void handleRequestThread(std::promise<int>*);


    /*! \public handleCliThread
     * @brief loop that receives new Requests from CLI and pushes to queue
     * @callgraph
     * @return RET::OK when CLI is exiting
     */
    void handleCliThread(std::promise<int>*);


    /*! \public pushRequest
    * @brief push incoming request to queue
    * @addtogroup QueueRequestOp
    * @callgraph
    * @param m_request incoming request about to be queued
    */
    void pushRequest(const Request &m_request);

    /*! \public popRequest
     * @brief pop requests from queue
     * @addtogroup QueueRequestOp
     * @callgraph
     * @return popped request ready to process
     */
    Request popRequest();

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
    bool m_queueEmpty;

    Cli *p_cli;

    Connection *p_conn;

    StatusLogger *m_logger;

    std::mutex m_lock;

    std::queue<Request> m_requests;

    std::condition_variable m_condVar;

    /*! \private Client::getCliInput(Cli* p_cli)
   * @brief A method that waits for CLI to process incoming request.
   * @param p_cli - pointer to CLI instance
   * @return - A request object
   */
    static Request getCliInput(Cli* p_cli);

};


#endif //MEDIAFW_CLIENT_H
