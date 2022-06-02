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
//////////////////////// MATRIZ DE TERRENOS //////////////////////////////
    std::vector<std::unique_ptr<Terrain> > matrix;
public:
    Map(int rows, int cols);
    ~Map();
    bool canMove(const Unit& unit, Position postion);
    bool isValid(Position position);
    void put(Position position, std::string value);
    void showMap();

/////////////////////////// MATRIZ DE TERRENOS //////////////////////////////
    Terrain& at(Position position);
    void showTerrain();
    void put(Building building);
    void occupy(Building building);
    Terrain at(int x, int y);
};

#endif //__MAP_H__
