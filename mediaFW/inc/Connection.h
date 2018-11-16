//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CONNECTION_H
#define MEDIAFW_CONNECTION_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <future>
#include "SshConnector.h"
#include "HttpConnector.h"
#include "Util.h"

class Connection{
public:
    Connection() : m_conn(new SshConnector), m_http(new HttpConnector){
        std::cout << "Connection constructor" << std::endl;
    }

    ~Connection() {
       // m_conn->disconnect();
    }

    bool getConnectionStatus() { return m_conn->m_currentlyConnected; }

    bool goSsh(std::promise<int>* obj) {
        // stream = m_conn->connect(23, "192.168.0.107");
        std::string result;
        for (std::string line; std::getline(std::cin, line); )
        {
            if(line.find(EXIT) != std::string::npos) {
                break;
            }
            stream->sendRemoteCommands(line, result);
        }
        obj->set_value(RET::OK);
        return getConnectionStatus();
    }

    bool sendServerRequest(Request &request, std::string &result) {
        if(getConnectionStatus()) {
            m_http->send(request);
            return true;
        }
        return false;
    }

private:
    SshConnector* m_conn;
    HttpConnector* m_http;
    ConnectionStream* stream;
};

#endif //MEDIAFW_CONNECTION_H
