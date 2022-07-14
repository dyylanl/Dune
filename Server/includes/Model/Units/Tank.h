#ifndef __TANK_H__
#define __TANK_H__

#include "Unit.h"

class Tank : public Unit {
public:
    Tank(int x, int y,int player_id);
    ~Tank();
    bool canMoveAboveTerrain(Terrain &terrain) override;
    virtual void reciveBonusDammage(const Weapon &weapon) override;
};

#endif
