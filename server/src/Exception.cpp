//
//  Exception.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/31/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Exception.hpp"

Exception::Exception(std::string const & msg) throw() : _e(msg)
{}

Exception::~Exception() throw()
{}

const char * Exception::what() const throw() {
    return _e.c_str();
}
