//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CONNECTION_H
#define MEDIAFW_CONNECTION_H

class Connection{
public:
    Connection(){
        connect();
        instantiateCli();
    }
    ~Connection() = default;

private:
    void connect();

    void instantiateCli();

};

#endif //MEDIAFW_CONNECTION_H
