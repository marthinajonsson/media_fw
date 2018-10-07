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
    Connection(){
        tryConnect();
    }

    ~Connection() {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
    };

    int sendRemoteCommands(std::string command);

private:
    ssh_session my_ssh_session;
    int rc;
    char *password;

    void tryConnect();
    int verify_knownhost(ssh_session session);

};

#endif //MEDIAFW_CONNECTION_H
