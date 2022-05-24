#ifndef __POSITION_H__
#define __POSITION_H__

#include <vector>

#define BLOCK_X 32
#define BLOCK_Y 32

class Position {
//private:

public:
    int x,y;

    Position();
    Position(int x, int y);

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    void normalizeToBlock();

    bool operator==(const Position& other) const;
    bool operator<(const Position& other) const;

    int sqrtDistance(const Position &pos) const;
};

#endif //__POSITION_H__
