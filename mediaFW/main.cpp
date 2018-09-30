#include <iostream>

class Media{
public:
    Media(){
        std::cout<<"media" <<std::endl;
        connect();
    }

private:
    void connect(){
        std::cout<<"Connecting.."<<std::endl;
        //TODO: Setup connection to Network
    }

};

class Cli {
public:
    Cli() {
        std::cout<<"cli" <<std::endl;
        cliDeamon();
    };
    ~Cli(){}
private:
    void cliDeamon(){
        std::cout<<"cli daemon started" <<std::endl;
    }
};

int main() {
    std::cout << "Hello, Worlds!" << std::endl;

    Media mm;

    Cli cli;
    return 0;
}