#ifndef __MAP_H__
#define __MAP_H__

#include <string>
#include "Position.h"
#include "Units/Unit.h"

class Map {
    std::vector<std::vector<std::string>> mapa;
    int rows, cols;
public:
    Map(int rows, int cols);
    ~Map();
    bool canMove(const Unit& unit, Position postion);
    bool isValid(Position position);
    void put(Position position, std::string value);
    void showMap();
};

#endif //__MAP_H__
