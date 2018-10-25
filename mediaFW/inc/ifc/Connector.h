//
// Created by mjonsson on 10/25/18.
//

#ifndef MEDIAFW_CONNECTOR_H
#define MEDIAFW_CONNECTOR_H

#include <netinet/in.h>
#include <libssh/libssh.h>
#include "ConnectionStream.h"

class Connector {
public:

    Connector() = default;
    ~Connector() = default;

    virtual ConnectionStream* connect(uint16_t port, std::string server) = 0;
    virtual void disconnect() = 0;

protected:
    virtual int resolveHost(ssh_session session) = 0;
};

#endif //MEDIAFW_CONNECTOR_H
