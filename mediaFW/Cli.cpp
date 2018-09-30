//
// Created by mjonsson on 9/30/18.
//

#include "Cli.h"

void Cli::process(const std::string &input) {
    std::string one = "etta";

    if(one == input){
        std::cout<<"Etta"<< std::endl;
    }
}

void Cli::daemon() {
    std::cout<<"cli daemon started" <<std::endl;
    std::string quit = "q";

    for (std::string line; std::cout << "APP > " && std::getline(std::cin, line); )
    {

        if(line == quit){
            std::cout<<"cli daemon stopped" <<std::endl;
            break;
        }
        else if (!line.empty()) {
            process(line);
        }
    }
}
