#ifndef __RAIDER_H__
#define __RAIDER_H__

#include "Unit.h"

class Raider : public Unit {
public:
    Raider(int x, int y, int player_id);
    ~Raider();
    bool canMoveAboveTerrain(Terrain &terrain) override;

    virtual void reciveBonusDammage(const Weapon &weapon) override;

    virtual void attack(Attackable* enemy);

};

#endif	// __RAIDER_H__
