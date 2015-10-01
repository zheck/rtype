//
//  QuadTree.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/9/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "QuadTree.hpp"

QuadTree::QuadTree(Vect2 const & origin, Vect2 const & dimension, int gameTime) :
_origin(origin),
_dimension(dimension),
_gameTime(gameTime)
{
    _tree.clear();
    _entities.clear();
    _a = NULL;
    _b = NULL;
    _c = NULL;
    _d = NULL;
    _midx = dimension.x / 2;
    _midy = dimension.y / 2;
}

QuadTree::~QuadTree()
{
    for (std::list<QuadTree *>::iterator it = _tree.begin(); it != _tree.end(); ++it) {
        delete *it;
    }
    _tree.clear();
    _entities.clear();
}

void QuadTree::createInfluenceTree(std::list<Entity *> &ennemies)
{
    for (std::list<Entity *>::iterator it = ennemies.begin(); it != ennemies.end(); ++it) {
        if ((*it)->isAlive()) {
            fill(*it);
        }
    }
}

void QuadTree::fill(Entity *entity)
{
    if (isRectContainRect(*entity)) {
        _entities.push_back(entity);
        if (_entities.size() > 5) {
            for (std::list<QuadTree *>::iterator it = _tree.begin(); it != _tree.end(); ++it) {
                (*it)->fill(entity);
            }
        }
        else if (_entities.size() == 5) {
            subdivide();
        }
    }
}

void QuadTree::subdivide()
{
    Vect2 v(_midx, _midy);
    _a = new QuadTree(Vect2(_origin.x, _origin.y), v, _gameTime);
    _b = new QuadTree(Vect2(_origin.x + _midx, _origin.y), v, _gameTime);
    _c = new QuadTree(Vect2(_origin.x, _origin.y + _midy), v, _gameTime);
    _d = new QuadTree(Vect2(_origin.x + _midx, _origin.y + _midy), v, _gameTime);
    _tree.push_back(_a);
    _tree.push_back(_b);
    _tree.push_back(_c);
    _tree.push_back(_d);
    for (std::list<Entity *>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
        for (std::list<QuadTree *>::iterator it2 = _tree.begin(); it2 != _tree.end(); ++it2) {
            (*it2)->fill(*it);
        }
    }
}

bool QuadTree::insert(Entity * entity)
{
    if (isRectContainRect(*entity)) {
        if (_entities.size() > 4) {

            for (std::list<QuadTree *>::iterator it = _tree.begin(); it != _tree.end(); ++it) {
                if ((*it)->insert(entity) == false) {
                    return false;
                }
            }
        }
        else {
            for (std::list<Entity *>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
                if (isCollision((**it), *entity) == true) {
                    entity->attack(*it, _gameTime);
                    return false;
                }
            }
        }
    }
    return true;
}

bool QuadTree::isCollision(const Entity &e1, const Entity &e2) {
    return (e1.posX() + e1.width() > e2.posX() &&
            e1.posX() < e2.posX() + e2.width() &&
            e1.posY() + e1.height() > e2.posY() &&
            e1.posY() < e2.posY() + e2.height());
}

bool QuadTree::isRectContainRect(Entity const & entity) {
    return (entity.posX() + entity.width() > _origin.x &&
            entity.posX() < _origin.x + _dimension.x &&
            entity.posY() + entity.height() > _origin.y &&
            entity.posY() < _origin.y + _dimension.y);
}


