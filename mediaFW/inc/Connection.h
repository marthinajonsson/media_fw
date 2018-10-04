//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CONNECTION_H
#define MEDIAFW_CONNECTION_H

#include <string>

class Connection{
public:
    Connection(){
        tryConnect();
    }

    std::string pullResult();

    ~Connection() = default;

private:
    void tryConnect();
    bool ssh2Echo();
    void write(std::string message);
    std::string read();

};

#endif //MEDIAFW_CONNECTION_H
