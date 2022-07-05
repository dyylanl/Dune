#ifndef __HEAVY_INFANTRY_H__
#define __HEAVY_INFANTRY_H__


#include "Unit.h"

class HeavyInfantry : public Unit{
public:
    HeavyInfantry(int x, int y);
    ~HeavyInfantry();
    virtual bool canMoveAboveTerrain(Terrain &terrain);

    virtual void shoot(Attackable& defender);
    virtual bool shotARocket();
    Rocket* viewRocket();
    virtual Rocket* getRocket();
    virtual void reciveBonusDammage(const Weapon &weapon);
private:
    Position pos;
    int life;
    bool shot;
    Rocket* rocket;
};

#endif	// __HEAVY_INFANTRY_H__