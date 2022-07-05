#ifndef __POSITION_H__
#define __POSITION_H__

#include <vector>
#include "../types.h"

class Position {

public:
    int x,y;
    Position();
    Position(int x, int y);
    int getX() const;
    int getY() const;
    bool operator==(const Position& other) const;
    bool operator<(const Position& other) const;
    int sqrtDistance(const Position &pos) const;
    void normalize();
};

#endif //__POSITION_H__
