//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CONNECTION_H
#define MEDIAFW_CONNECTION_H

#include <libssh/libssh.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <string>


class Connection{
public:
    Connection() : m_currentlyConnected(false){
        establishSshConnect();
    }

    ~Connection() {
        std::cout << "Deconstruct ssh connection" << std::endl;
        ssh_disconnect(m_ssh_session);
        ssh_free(m_ssh_session);
        m_currentlyConnected = false;
    };

    bool getConnectionStatus() { return m_currentlyConnected; }
    bool sendRemoteCommands(std::string request, std::string &result);

private:
    ssh_session m_ssh_session;
    int m_result;
    bool m_currentlyConnected;
    char *m_password;
    void establishSshConnect();
    int verifyHost(ssh_session session);
};

#endif //MEDIAFW_CONNECTION_H
