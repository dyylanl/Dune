#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include <memory>
#include <iostream>
#include "../Attackable.h"
#include "../Terrains/Terrain.h"
#include "../Player.h"

class Map;

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

    Unit(const int x, const int y, const int hitPoints, const int speed, const int cost);
    ~Unit();
    bool operator==(const Unit& other);
    void setPath(std::stack<Position> path, Position destiny);
    bool move(Map &map);
    void follow(Attackable* other, Map& map);
    bool isAttacking();
    void setPlayer(Player &player);
    Player& getPlayer();
    void checkForDeadVictim();
    bool hasNews();

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
    Player* player;
    bool news;
};

#endif //__UNIT_H__
