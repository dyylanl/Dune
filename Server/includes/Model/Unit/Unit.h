#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include "../Position.h"

class Unit {
public:
    void setPath(std::stack<Position> path, Position destiny);
    Unit(int x, int y, int speed);
    Position& getPosition();
    virtual ~Unit();
    virtual bool canMove();

protected:
    const int speed;
    std::stack<Position> pathToDestiny;
    Position destiny;
    Position next_pos;
    Position pos;

};

#endif //__UNIT_H__