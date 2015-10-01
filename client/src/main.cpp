//
//  main.cpp
//  R-Type
//
//  Created by Zhou Fong on 10/11/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "Client.hpp"

int main(int ac, char ** av)
{
    if (ac < 2) {
        std::cerr << "Usage: ./client serverPort" << std::endl;
        return 1;
    }
    Client client(av[1]);
    
    client.run();
    return 0;
}