//
//  Exception.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/31/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Exception__
#define __R_TypeServer__Exception__

# include <exception>
# include <iostream>

class Exception : public std::exception
{
    std::string _e;
    
public:
    Exception(std::string const &) throw();
    virtual ~Exception() throw();
    
    Exception & operator=(Exception const &);
    virtual const char * what() const throw();
};

#endif /* defined(__R_TypeServer__Exception__) */
