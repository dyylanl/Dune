#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "../../config/MapReader.h"
#include "Terrains/Terrain.h"
#include "Area.h"
#include "DTOs/MapDTO.h"
#include "DTOs/BuildingDTO.h"



class Map {
    MapReader map_reader;
    int rows, cols;
    bool news;
    ////////////////// IMPLEMENTACION CON TERRENOS //////////////////
    std::vector<std::vector<Terrain>> terrrains; // contiene el tipo de terreno en esa pos
    std::vector<std::vector<char>> mapa; // contiene el tipo de unidad en esa posicion
    std::vector<BuildingDTO> buildingsDTO;
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


    void moveUnit(Position start, Position end, std::vector<Position*> path);


};

#endif //__MAP_H__