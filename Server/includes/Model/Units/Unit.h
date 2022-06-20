#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include <memory>
#include <iostream>
#include "../Position.h"

class Unit {
private:
    int id;
    static int counter;
    char unitType;
    Position position;
public:
    Unit(int id, char type, int x, int y);
    ~Unit();

    Position getPosition();
    static bool canMove();
    char getUnitType();
    int getId();
    void setPosition(Position pos);

    enum UnitType {
        HARVESTER,
        LIGHT_INFANTRY,
        HEAVY_INFANTRY,
        RAIDER,
        TANK,
        TRIKE,
    };
};

#endif //__UNIT_H__
