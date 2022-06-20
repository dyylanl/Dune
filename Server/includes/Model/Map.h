#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "Position.h"
#include "Units/Unit.h"
#include "Terrains/Terrain.h"
#include "Buildings/Building.h"
#include "../../config/MapReader.h"

class Map {
    MapReader map_reader;
    int rows, cols;
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    std::vector<std::vector<Terrain>> terrrains;
    std::vector<std::vector<char>> mapa;
public:
    explicit Map(std::string map_path);
    ~Map();
    bool canMove(const Unit& unit, Position postion);
    bool isValid(Position position);
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    void putTerrain(Terrain terrain);
    void showTerrain();
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    std::vector<std::vector<char>> getMap() {return this->mapa;}
    char getTypeTerrain(int posX, int posY);



    // comandos
    /*
     * FALTA TERMINAR: retorna la unidad si en el mapa de char hay una 'U'.
     */
    Unit* selectUnit(int pos_x, int pos_y);

    /*
     * FALTA TERMINAR: construye un edificio en la pos indicada si no hay nada
     */
    void build(char type, int x, int y);

};

#endif //__MAP_H__