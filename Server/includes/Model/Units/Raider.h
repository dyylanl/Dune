#ifndef __RAIDER_H__
#define __RAIDER_H__

#include "Unit.h"

class Raider : public Unit {
public:
    Raider(int x, int y);
    ~Raider();
    bool canMoveAboveTerrain(Terrain &terrain) override;

    virtual void reciveBonusDammage(const Weapon &weapon) override;
};

#endif	// __RAIDER_H__
