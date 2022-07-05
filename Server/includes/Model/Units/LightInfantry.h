#ifndef __LIGHT_INFANTRY_H__
#define __LIGHT_INFANTRY_H__

#include "Unit.h"

class LightInfantry : public Unit {
public:
    LightInfantry(int x, int y);

    ~LightInfantry();

    bool canMoveAboveTerrain(Terrain &terrain) override;

    virtual void reciveBonusDammage(const Weapon &weapon) override;
};

#endif