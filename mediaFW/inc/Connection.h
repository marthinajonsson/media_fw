//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CONNECTION_H
#define MEDIAFW_CONNECTION_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include "SshConnector.h"


class Connection{
public:
    Connection() : m_conn(new SshConnector){
        std::cout << "Connection constructor" << std::endl;
       // stream = m_conn->connect(23, "192.168.0.107");
    }

    ~Connection() {
       // m_conn->disconnect();
    }

    bool getConnectionStatus() { return m_conn->m_currentlyConnected; }

    bool sendServerRequest(std::string &request, std::string &result) {
        if(m_conn->m_currentlyConnected) {
            return stream->sendRemoteCommands(request, request);
        }
        return false;
    }

private:
    SshConnector* m_conn;
    ConnectionStream* stream;
};

#endif //MEDIAFW_CONNECTION_H
