#ifndef __TRIKE_H__
#define __TRIKE_H__

#include "Unit.h"

class Trike : public Unit {
public:
    Trike(int x, int y,int player_id);
    ~Trike();
    bool canMoveAboveTerrain(Terrain &terrain) override;
    virtual void reciveBonusDammage(const Weapon &weapon) override;
};

#endif
