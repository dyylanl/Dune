#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "Position.h"
#include "Units/Unit.h"
#include "Terrains/Terrain.h"
#include "Buildings/Building.h"

class Map {
    int rows, cols;
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    std::vector<std::vector<Terrain>> terrrains;
public:
    Map(int rows, int cols);
    ~Map();
    bool canMove(const Unit& unit, Position postion);
    bool isValid(Position position);
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    void putTerrain(Terrain terrain);
    void showTerrain();
};

#endif //__MAP_H__