#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include <memory>
#include <iostream>
#include "Attackable.h"
#include "../Terrains/Terrain.h"
#include "../Weapons/Rocket.h"


class Unit : public Attackable {
public:
    enum UnitType {
        HARVESTER,
        LIGHT_INFANTRY,
        HEAVY_INFANTRY,
        RAIDER,
        TANK,
        TRIKE,
    };
    Unit(int x, int y, int hitPoints, int speed, int cost);
    bool operator==(const Unit& other);
    void setPath(std::stack<Position> path, Position destiny);
    bool move(Map &map);
    void follow(Attackable* other, Map& map);
    virtual bool canMoveAboveTerrain(Terrain& terrain) = 0;
    //void setPlayer(Player &player);
    //Player& getPlayer();
    virtual bool shotARocket();
    virtual Rocket* getRocket();
    void checkForDeadVictim();
    virtual bool hasNews();
    bool isAttacking();
    void makeAction(Map &map);
public:
    const int id;
protected:
    static int counter;
    const int speed;
    const int cost;
    int actual_speed;
    std::stack<Position> pathToDestiny;
    Attackable* foll_unit;
    Position destiny;
    Position prev_foll_unit_pos;
    Position next_pos;
    //Player* player;
    bool news;
};

#endif //__UNIT_H__
