#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include <memory>
#include <iostream>
#include "../Position.h"

class Map;

class Unit {
private:
    int id;
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
};

#endif //__UNIT_H__
