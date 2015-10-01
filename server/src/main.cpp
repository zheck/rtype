//
//  main.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Server.hpp"
#include "Exception.hpp"

int main(int ac, char ** av)
{
    if (ac < 2) {
        std::cerr << "Usage ./server Port" << std::endl;
        return 1;
    }
    Server s;
    try {
        s.init(av[1]);
        s.run();
    }
    catch (Exception & e) {
        std::cerr << "Exception caught " << e.what() << std::endl;
    }
    return 0;
}
