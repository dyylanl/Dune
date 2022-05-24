#ifndef __MAP_H__
#define __MAP_H__


#include <iostream>
#include <vector>
#include "Unit/Unit.h"

#define BLOCK_HEIGHT 32
#define BLOCK_WIDTH 32

class Map {

private:
    int rows, columns;
    std::vector<std::vector<std::string>> world;
     // METODOS PRIVADOS
    std::string getPos(int x, int y);
public:
    Map(int x, int y);
    void showMap();
    ~Map();


    void setValue(int x, int y, char value);


    static bool canMove(Unit& unit, Position pos);
    bool isValid(Position& pos);
};


#endif
