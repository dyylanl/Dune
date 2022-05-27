#ifndef __POSITION_H__
#define __POSITION_H__

#include <vector>

#define BLOCK_X 1
#define BLOCK_Y 1

class Position {
//private:

public:
    int x,y;

    Position();
    Position(int x, int y);
    Position(const Position &other);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    bool operator==(const Position& other) const;
    bool operator<(const Position& other) const;
    bool operator!=(const Position& other) const;
    Position operator+(const Position& other) const;
    Position& operator=(const Position& other);
    int sqrtDistance(const Position &pos) const;
};

#endif //__POSITION_H__
