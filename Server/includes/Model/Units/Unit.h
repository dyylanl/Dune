#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include <memory>
#include <iostream>
#include "../Position.h"

class Map;

class Unit {
private:
    Position position;
public:
    Unit(int x, int y);
    ~Unit();
    Position getPosition();

    static bool canMove();
};

#endif //__UNIT_H__
