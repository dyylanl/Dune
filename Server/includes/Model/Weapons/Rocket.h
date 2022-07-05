#ifndef __ROCKET_H__
#define __ROCKET_H__


#include "../Position.h"

class Map;

class Rocket{
public:
    Rocket(Position source, Position dest);
    void move();
    bool arrived();
    void explode(Map& map);
    Position& getPosition();

    const int id;
private:
    static int counter;
    Position pos;
    Position dest;
};

#endif	// __ROCKET_H__
