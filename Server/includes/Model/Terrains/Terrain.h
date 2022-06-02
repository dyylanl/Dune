#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "../Buildings/Building.h"

class Terrain {
protected:
    char key;
    bool occupied;
    int speed_factor;
public:
    Terrain();
    explicit Terrain(char key);
    void occupy();
    bool isOccupied();
    int getSpeedFactor();
    bool operator==(const Terrain& terrain);
    virtual char getKey();
    virtual void buildOn(Building building);

};

#endif	// __TERRAIN_H__
