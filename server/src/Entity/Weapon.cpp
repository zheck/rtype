//
//  Weapon.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Weapon.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "ShockWave.hpp"

Weapon::Weapon()
{
    _bulletType = BULLET;
    _ammo = 0;
    _lastFired = 0;
    _cooldown = 3000;
    _missile[BULLET] = &Weapon::bullet;
    _missile[SHOCK_WAVE] = &Weapon::shockWave;
}

Weapon::~Weapon()
{}

void Weapon::reinit()
{
    _ammo = 0;
    _bulletType = BULLET;
}

void Weapon::fire(eType bulletType, Vect2 const & position, Vect2 const & direction)
{
    if (_ammo <= 0) {
        _bulletType = BULLET;
    }
    if (_delegate != NULL && bulletType == BULLET) {
        if (_missile.find(_bulletType) != _missile.end()) {
            Entity * e = (this->*_missile[_bulletType])(position, direction);
            _delegate->addMissile(e);
            --_ammo;
        }
    }
}

Entity * Weapon::bullet(Vect2 const &position, Vect2 const &direction)
{
    Entity * e = new Bullet(position, direction);
    return e;
}

Entity * Weapon::shockWave(Vect2 const &position, Vect2 const &direction)
{
    Entity * e = new ShockWave(position, direction);
    return e;
}

Entity * Weapon::megaAttack(const Vect2 &position, const Vect2 &direction)
{
    Entity * e = new MegaAttack(position, direction);
    return e;
}

bool Weapon::setBulletType(eType bulletType)
{
    if (bulletType == BULLET) {
        return false;
    }
    if (_missile.find(bulletType) != _missile.end()) {
        _ammo = BONUS_AMMO;
        _bulletType = bulletType;
        return true;
    }
    return false;
}

void Weapon::setDelegate(Game * g)
{
    _delegate = g;
}