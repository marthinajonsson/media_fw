//
// Created by mjonsson on 10/25/18.
//

#ifndef MEDIAFW_SSHCONNECTOR_H
#define MEDIAFW_SSHCONNECTOR_H

//
// Created by mjonsson on 10/25/18.
//


#include <ifc/Connector.h>
#include <ConnectionStream.h>
#include "StatusLogger.h"
#include <libssh/libssh.h>
#include <iostream>
#include <cstring>
#include <cstring>
#include <errno.h>

class SshConnector : public Connector {

public:
    SshConnector() : m_currentlyConnected(false), m_logger(new StatusLogger) {}
    ~SshConnector() = default;

    bool m_currentlyConnected;

    ConnectionStream* connect(uint16_t port, std::string server) override;
    void disconnect () override;

protected:
    int resolveHost(ssh_session session) override;

private:
    StatusLogger *m_logger;
    ssh_session m_session{ };
    unsigned char *m_hash = nullptr;
    char *m_hexa{ };
};

#endif //MEDIAFW_SSHCONNECTOR_H
