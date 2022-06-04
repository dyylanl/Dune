#ifndef __TERRAIN_H__
#define __TERRAIN_H__


#include "../Position.h"

class Terrain {
protected:
    Position position;
    char type;
    bool occupied;
    int speed_factor;
public:
    Terrain(Position pos, char type);
    void occupy();
    bool isOccupied() const;
    int getSpeedFactor() const;
    bool operator==(const Terrain& terrain);
    char getType();
    Position getPosition();
    void setType(char type);
    Terrain& operator=(const Terrain& otro);
};

#endif	// __TERRAIN_H__
