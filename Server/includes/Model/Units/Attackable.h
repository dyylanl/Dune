#ifndef __ATTACKABLE_H__
#define __ATTACKABLE_H__

#include "../Position.h"
#include "../Weapons/Weapon.h"

class Attackable {
protected:
    int initial_life;
    int life;
    Position pos;

public:
    explicit Attackable(const int life, const int x, const int y);
    virtual ~Attackable() = default;
    void setPosition(Position pos);

    virtual Position& getPosition();
    virtual Position& getClosestPosition(Position& pos);
    virtual int getLife();
    virtual int getInitialLife();
    virtual void reciveAttack(const Weapon &weapon);
    virtual void reciveBonusDammage(const Weapon &weapon) = 0;
    static bool isDead(const Attackable *unit);
};

#endif //__ATTACKABLE_H__
