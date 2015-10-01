//
//  IEntity.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef R_TypeServer_IEntity_h
#define R_TypeServer_IEntity_h

#include "defines.hpp"
#include "Vect2.hpp"

class IEntity
{
public:
    virtual ~IEntity() {}

    virtual eType getType() const = 0;
    virtual bool isAlive() const = 0;
    virtual Vect2 & getPosition() = 0;
    virtual Vect2 & getSize() = 0;
    virtual void setPosition(int px, int py) = 0;
    virtual void update(int gameTime) = 0;
    virtual int getId() const = 0;
};

#endif
