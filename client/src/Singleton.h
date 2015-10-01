//
//  Singleton.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/14/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef xCodeClient_Singleton_h
#define xCodeClient_Singleton_h

template<typename T>
class Singleton
{
private:
    static T _singleton;
    
protected:
    Singleton() {}
    Singleton(Singleton const & rhs);
    virtual ~Signleton() {}
    
    Singleton & operator=(Singleton const & rhs);
    
public:
    static T & getInstance();
    static void kill() = 0;
};

template<typename T>
T & Singleton<T>::getInstance()
{
    return _singleton;
}


#endif
