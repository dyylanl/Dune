#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "../../config/MapReader.h"
#include "Terrains/Terrain.h"
#include "Area.h"
#include "DTOs/MapDTO.h"
#include "DTOs/BuildingDTO.h"
#include "DTOs/UnitDTO.h"


class Map {
    MapReader map_reader;
    int rows, cols;
    bool news;
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    std::vector<std::vector<Terrain>> terrrains; // contiene el tipo de terreno en esa pos
    std::vector<std::vector<char>> mapa; // contiene el tipo de unidad en esa posicion



    std::vector<BuildingDTO> buildingsDTO;
    std::vector<UnitDTO> unitsDTO;


public:
    ~Map();
    bool hasNews();
    int getRows() const {return rows;}
    int getCols() const {return cols;}

    std::vector<std::vector<char>>& getMap();
    
    char getTypeTerrain(int posX, int posY);

    /*
     * retorna true si es una posicion dentro del mapa
     */
    bool isValid(Position& pos);


    int getHeight();
    int getWidth();
    int getWidthInBlocks();
    int getHeightInBlocks();
    int getBlockWidth();
    int getBlockHeight();


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
    void getInitialPositions();
    
    Position getClosestSpeciaPosition(Position pos, int radius);

    void updateSpice(int x, int y);

    explicit Map(std::string path_config);

    std::vector<BuildingDTO> getBuildings();

    /*
    *   Al player de id le asigna una unidad del type en posicion x,y
    */
    void putUnit(InstanceId id_player, char type, int x, int y);

    /*
    *   Le asigna una building al player del type en la pos x,y
    */
    void putBuilding(InstanceId id_player, char type, int x, int y);

    /*
    *   
    */
    std::vector<UnitDTO> getUnits();

};

#endif //__MAP_H__