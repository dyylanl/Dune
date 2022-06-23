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
    std::vector<Building*> builds;
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
     * FALTA TERMINAR: selecciona la unidad si en el mapa de char hay una 'U'.
     */
    void selectUnit(int pos_x, int pos_y);

    /*
     * FALTA TERMINAR: construye un edificio en la pos indicada si no hay nada
     */
    void build(char type, int x, int y);




    bool isValid(Position& pos);
    bool canMove(Unit& unit, Position pos);
    void put(Unit& unit);
    void put(Building* building);
    void occupy(Building* building);
    /*
     * limpio la construccion del terreno
     */
    void free(Building& building);
    int getHeight();
    int getWidth();
    int getWidthInBlocks();
    int getHeightInBlocks();
    int getBlockWidth();
    int getBlockHeight();
    /*
     * retorna true si en esa pos se puede construir con tal alto y ancho
     */
    bool canWeBuild(Position& pos, int width, int height);
    /*
     * devuelve la posicion libre mas cercana al build
     */
    Position getClosestFreePosition(Building* building);
    /*
     * retorna la posicion de la esquina segun el ancho y alto seteados
     */
    static Position getCornerPosition(Position& pos);
    /*
     * devuelve el tipo de terreno que hay en la pos x,y
     */
    Terrain& at(int x, int y);

    Terrain& blockAt(int x, int y);
    Terrain& at(const Position& pos);
    int getSpeedFactorAt(Position& pos);


    void setDestiny(Unit &unit, int x_dest, int y_dest);



};

#endif //__MAP_H__