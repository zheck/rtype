//
//  ResourcePath.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/9/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <unistd.h>

#include "ResourcePath.hpp"

std::string resourcePath()
{
    char path[255];
    
    getcwd(path, 255);
    std::string str = path;
    return str;
}