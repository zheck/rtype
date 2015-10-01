#ifndef _VECT2F_HPP
#define _VECT2F_HPP

class Vect2f
{
public:
    float x;
    float y;
    
public:
    Vect2f() {}
    Vect2f(float fx, float fy) : x(fx), y(fy) {}
    Vect2f(Vect2f const & rhs) : x(rhs.x), y(rhs.y) {}
    ~Vect2f() {}
    
    Vect2f & operator=(Vect2f const & rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    
    Vect2f operator+(Vect2f const & rhs) {
        return Vect2f(x + rhs.x, y + rhs.y);
    }
};

#endif