//
// Created by mjonsson on 10/4/18.
//

#ifndef MEDIAFW_CLIENT_H
#define MEDIAFW_CLIENT_H
#include <algorithm>
#include <queue>
#include <mutex>
#include <future>

#include "ifc/Subject.h"
#include "Connection.h"
#include "Cli.h"
#include "StatusLogger.h"

class Client : Subject{

public:

    /*! \public Client constructor()
    * @brief Instantiates database type DbType_e and corresponding Database.
    */
    Client(Connection *_conn, Cli* _cli) : p_conn(_conn), p_cli(_cli),  m_logger(new StatusLogger) {
        std::cout << "Client constructor" << std::endl;
    };

    Client() = default;

    /*! \public Client deconstructor()
    * @brief deletes previous instantiated Database.
    */
    ~Client() = default;

    /*! \public Client::setup()
    * @brief A method that waits for input from private method Client::getCliInput().
    * The method will break if input is interpreted as exit or
    * continues by having the request handled in Client::handleCallback().
    */
    int waitCliAsync();

    bool getConnectionStatus () { return p_conn->getConnectionStatus(); }

    /*
     * Overriden methods implementing subject pattern
     *
     * */
    void registerObserver(Observer *observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer) override {
        auto iterator = std::find(observers.begin(), observers.end(), observer);

        if (iterator != observers.end()) { // observer found
            observers.erase(iterator); // remove the observer
        }
    }

    void notifyObservers(Request &request) override {
        for (Observer *observer : observers) { // notify all observers
            observer->update(request);
        }
    }

    void push(const Request &m_request) {
        std::unique_lock<std::mutex> guard(m_lock);
        if(m_requests.empty()) {
            m_emptyQ.notify_one();
        }
        m_requests.push(m_request);
    }

    Request pop() {
        std::unique_lock<std::mutex> guard(m_lock);
        if(m_requests.empty()) {
            Request err(RET::ERROR, "No request to pop");
            return err;
        }
        auto popped = m_requests.front();
        m_requests.pop();
        return popped;
    }



    std::vector<Observer *> observers;

private:

    /*! \privatesection Connection* p_conn.
     * @brief Private pointer to connection object.
     */
    Connection *p_conn;


    /*! \privatesection Cli* p_cli.
     * @brief Private pointer to a cli object
     */
    Cli *p_cli;


    StatusLogger *m_logger;

    std::queue<Request> m_requests;

    mutable std::mutex m_lock;

    std::condition_variable m_emptyQ;


    /*! \privatesection Client::getCliInput(Cli* p_cli)
     * @brief A method that waits for CLI to process incoming request. Used by std::future.
     * @param p_cli
     * @return A vector of strings containing the result of CLI process
     */
    static Request getCliInput(Cli* p_cli) {
        return p_cli->process();
    }

    /*! \privatesection Client::handleCallback(std::vector<std::string request , bool connected)
     * @brief handles the clients requests to the server.
     * @param request - String containing all information needed for the server request.
     * @param connected - Boolean parameter indicating we have an established ssh connection.
     */
    void handleRequest();
};


#endif //MEDIAFW_CLIENT_H
