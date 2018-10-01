//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CONNECTION_H
#define MEDIAFW_CONNECTION_H

class Connection{
public:
    Connection(){
        tryConnect();
        instantiateCli();
    }
    ~Connection() = default;

private:
    void tryConnect();
    bool ssh2Echo();
    void instantiateCli();

};

#endif //MEDIAFW_CONNECTION_H
