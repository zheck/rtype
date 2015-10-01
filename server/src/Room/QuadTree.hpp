//
//  QuadTree.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/9/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__QuadTree__
#define __R_TypeServer__QuadTree__

#include <iostream>
#include <list>

#include "Entity.hpp"
#include "Vect2.hpp"

class QuadTree
{
    std::list<QuadTree *> _tree;
    std::list<Entity *> _entities;
    Vect2 _origin;
    Vect2 _dimension;
    int _midx;
    int _midy;
    int _gameTime;
    
    QuadTree * _a;
    QuadTree * _b;
    QuadTree * _c;
    QuadTree * _d;

public:
    QuadTree(Vect2 const & origin, Vect2 const & dimension, int gameTime);
    QuadTree(QuadTree const & rhs);
    ~QuadTree();
    
    QuadTree & operator=(QuadTree const & rsh);

    void createInfluenceTree(std::list<Entity *> & ennemies);
    bool isRectContainRect(Entity const & entity);
    void fill(Entity * entity);
    void subdivide();
    bool insert(Entity * entity);
    bool isCollision(Entity const & e1, Entity const & e2);
};

#endif /* defined(__R_TypeServer__QuadTree__) */
