#ifndef __HARVESTER_H__
#define __HARVESTER_H__

#include "Unit.h"
#include "../Map.h"
class Harvester : public Unit {
public:
    Harvester(int x, int y);
    ~Harvester();
    virtual bool canMoveAboveTerrain(Terrain &terrain);
    virtual void reciveBonusDammage(const Weapon &weapon) override;


    bool farm(Map& map);
    bool isFull();

private:
    const int spiceCapacity;
    int spiceCollected;
    Position farming_position;
    int farm_speed;
    int actual_farm_speed;
    int load_speed;
    int actual_load_speed;
};

#endif
