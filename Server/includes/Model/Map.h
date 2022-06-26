#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "../../config/MapReader.h"
#include "Terrains/Terrain.h"
#include "Units/Unit.h"
#include "../Control/NewConnection.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "Area.h"
#include "DTOs/MapDTO.h"

class Map {
    MapReader map_reader;
    int rows, cols;
    bool news;
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    std::vector<std::vector<Terrain>> terrrains; // contiene el tipo de terreno en esa pos
    std::vector<std::vector<char>> mapa; // contiene el tipo de unidad en esa posicion
    std::vector<Unit*> units;
    std::vector<Building*> buildings;
public:
    ~Map();
    bool hasNews();
    bool canMove(const Unit& unit, Position postion);
    int getRows() const {return rows;}
    int getCols() const {return cols;}

    std::vector<std::vector<char>>& getMap();
    
    char getTypeTerrain(int posX, int posY);
    // comandos
    void selectUnit(int pos_x, int pos_y);
    /*
     * retorna true si es una posicion dentro del mapa
     */
    bool isValid(Position& pos);
    /*
     * retorna true si la unidad se puede mover hacia pos
     */
    bool canMove(Unit& unit, Position pos);
    /*
     * agrega una unidad a la lista de unidades
     */
    void put(Unit& unit);
    /*
     * agrega una constuccion a la lista de construcciones
     */
    void put(Building* building);
    /*
     * pone en el MAPA de terrenos la construccion
     */
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
     * devuelve la posicion libre mas cercana al build
     */
    Position getClosestFreePosition(Building* building);
    /*
     * retorna la posicion de la esquina segun el ancho y alto seteados
     */
    //static Position getCornerPosition(Position& pos);
    /*
     * devuelve el tipo de terreno que hay en la pos x,y
     */
    Terrain& at(int x, int y);
    /*
     *
     */
    Terrain& blockAt(int x, int y);
    /*
     * devuelve el tipo de terreno que hay en pos
     */
    Terrain& at(const Position& pos);
    /*
     * devuelve el factor de velocidad que hay en pos
     */
    int getSpeedFactorAt(Position& pos);
    /*
     * setea la ruta de destino de la unidad
     */
    void setDestiny(Unit &unit, int x_dest, int y_dest);
    void getInitialPositions();
    Unit *getClosestUnit(Position pos, int limitRadius, Player &player);
    std::vector<Unit *> getUnitsInArea(Area &area, Player &player);
    std::vector<Unit *> getUnitsInArea(Area &area);
    std::vector<Building *> getBuildingsInArea(Area &area);
    void cleanUnit(Unit *unit);
    void cleanBuilding(Building *building);
    bool canWeBuild(Position &pos, int width, int height, Player &player);
    Position getClosestSpeciaPosition(Position pos, int radius);
    std::vector<Building *> getBuildingsInArea(Area &area, Player &player);
    void updateSpice(int x, int y);
    Attackable *getClosestAttackable(Position &position, int limitRadius, Player &player);


    explicit Map(std::string path_config);

    /*
     * retorna 0 si el mapa esta completo
     * 1 si todavia no esta completo
     */
    int addPlayer(NewConnection* new_player);

};

#endif //__MAP_H__