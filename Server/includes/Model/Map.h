#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "Position.h"
#include "Units/Unit.h"
#include "Terrains/Terrain.h"
#include "Buildings/Building.h"

class Map {
    std::vector<std::vector<std::string>> mapa;
    int rows, cols;
    bool validPosition(Position position);
public:
    Map(int rows, int cols);
    ~Map();
    bool canMove(const Unit& unit, Position postion);
    void put(Position position, std::string value);
    void showMap();
    bool isValid(Position position);

};

#endif //__MAP_H__