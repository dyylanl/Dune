#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include <memory>
#include <iostream>
#include "../Objects/Attackable.h"
#include "../Map.h"


class Unit : public Attackable {
public:

    enum UnitType {
        LIGHT_INFANTRY,
        FREMEN,
        HEAVY_INFANTRY,
        SARDAUKAR,
        TRIKE,
        SONIC_TANK,
        RAIDER,
        DEVIATOR,
        TANK,
        DEVASTATOR,
        HARVESTER
    };

    Unit(const int x, const int y, const int hitPoints, const int speed, const int cost);
    virtual ~Unit();

    bool operator==(const Unit& other);

    void setPath(std::stack<Position> path, Position destiny);

    bool move(Map &map);

    virtual void makeAction(Map &map);

    virtual void actionOnPosition(Map& map, Position& pos);

    void follow(Attackable* other, Map& map);

    virtual bool canMoveAboveTerrain(Terrain& terrain) = 0;

    bool isAttacking();
/*
    void setPlayer(Player &player);
    Player& getPlayer();
    virtual bool shotARocket();
    virtual Rocket* getRocket();
*/
    void checkForDeadVictim();

    bool isTraining();

    void finishTraining();


    virtual bool hasNews();

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
    bool news;
};

#endif //__UNIT_H__
