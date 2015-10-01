//
//  Vect2.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef R_TypeServer_Vect2_h
#define R_TypeServer_Vect2_h

class Vect2
{
public:
    int x;
    int y;
    
public:
    Vect2() {}
    Vect2(int fx, int fy) : x(fx), y(fy) {}
    Vect2(Vect2 const & rhs) : x(rhs.x), y(rhs.y) {}
    ~Vect2() {}
    
    Vect2 & operator=(Vect2 const & rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    
    Vect2 operator+(Vect2 const & rhs) {
        return Vect2(x + rhs.x, y + rhs.y);
    }
};

#endif
