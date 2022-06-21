#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "Position.h"
#include "Units/Unit.h"
#include "Terrains/Terrain.h"
#include "Buildings/Building.h"
#include "../../config/MapReader.h"
#include "Area.h"

class Map {
    MapReader map_reader;
    int rows, cols;
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    std::vector<std::vector<Terrain>> terrrains; // contiene el tipo de terreno en esa pos
    std::vector<std::vector<char>> mapa; // contiene el tipo de unidad en esa posicion
    std::vector<Unit*> units;
public:
    explicit Map(std::string map_path);
    ~Map();
    bool canMove(const Unit& unit, Position postion);
    //bool isValid(Position position);
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




    bool isValid(Position& pos);
    bool canMove(Unit& unit, Position pos);
    void put(Unit& unit);
    void put(Building* building);
    void occupy(Building* building);
    void free(Building& building);
    int getHeight();
    int getWidth();
    int getWidthInBlocks();
    int getHeightInBlocks();
    int getBlockWidth();
    int getBlockHeight();
    bool canWeBuild(Position& pos, int width, int height, Player& player);
    Position getClosestFreePosition(Building* building);
    Position getCornerPosition(Position& pos);
    Position getClosestSpeciaPosition(Position pos, int radius);
    Terrain& at(int x, int y);
    Terrain& blockAt(int x, int y);
    Terrain& at(const Position& pos);
    int getSpeedFactorAt(Position& pos);


};

#endif //__MAP_H__