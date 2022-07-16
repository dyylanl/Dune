#ifndef __HARVESTER_H__
#define __HARVESTER_H__

#include <iostream>
#include "Unit.h"
#include "../Buildings/Refinery.h"
#include "../Terrains/Sand.h"
#include "../Terrains/Rock.h"
#include "../Terrains/Dunes.h"
#include "../Map.h"
#include "../Player.h"


class Harvester : public Unit {
public:
    Harvester(int x, int y, int player_id);

    ~Harvester();

    bool canMoveAboveTerrain(Terrain &terrain) override;
    virtual void reciveBonusDammage(const Weapon &weapon) override;
    virtual void actionOnPosition(Map& map, Position& pos) override;
    void makeAttack(Map &map) override;
    bool farm(Map& map);
    bool isFull();
    
    virtual void attack(Attackable* enemy) override;


private:
    const int spiceCapacity;
    int spiceCollected;
    Position farming_position;
    Refinery* refinery;
    int farm_speed;
    int actual_farm_speed;
    int load_speed;
    int actual_load_speed;
    bool farming;
    bool loading;

    void makeFarming(Map &map);
    void makeLoading(Map &map);

};

#endif