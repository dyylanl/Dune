#ifndef __MAP_H__
#define __MAP_H__


#include <string>
#include "../../config/MapReader.h"
#include "Terrains/Terrain.h"
#include "Area.h"
#include "DTOs/MapDTO.h"
#include "DTOs/BuildingDTO.h"
#include "DTOs/UnitDTO.h"
#include "Buildings/ConstructionCenter.h"
#include "Units/Unit.h"


class Map {

    MapReader map_reader;
    int rows, cols;
    int max_players;
    std::map<int, ConstructionCenter*> centers;
    std::vector<std::vector<Terrain>> terrrains; // contiene el tipo de terreno en esa pos
    std::vector<std::vector<char>> mapa; // contiene el tipo de terreno_key para enviar a los clientes


    std::vector<Building*> buildings;
    std::vector<Unit*> units;


    void loadConstructionsCenter();


public:

    /*
    *   Recibe por parametro la ruta al archivo del mapa.yaml para inicializarse
    */
    explicit Map(std::string path_config);

    int getMaxPlayers() {return max_players;}

    /*
    *   Destructor de mapa
    */
    ~Map();

    /*
    *   Getters del mapa
    */
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    int getHeight();
    int getWidth();
    int getWidthInBlocks();
    int getHeightInBlocks();
    int getBlockWidth();
    int getBlockHeight();

    /*
    *   Devuelve una matriz de char con cada clave del terreno
    */
    std::vector<std::vector<char>>& getMap();
    
    /*
    *   Devuelve el tipo de terreno en la posicion indicada
    */
    char getTypeTerrain(int posX, int posY);

    /*
     * retorna true si es una posicion valida en el mapa creado
     */
    bool isValid(Position& pos);

    /*
     * devuelve el tipo de terreno que hay en la pos x,y
     */
    Terrain& at(int x, int y);

    /*
     * devuelve el tipo de terreno que hay en pos
     */
    Terrain& at(const Position& pos);

    /*
     * devuelve el factor de velocidad que hay en pos
     */
    int getSpeedFactorAt(Position& pos);

    /*
    *   Retorna la especia a una distancia x de la posicion indicada
    */
    Position getClosestSpeciaPosition(Position pos, int radius);

    /*
    *   Resetea la especia al valor inicial del mapa
    */
    void updateSpice(int x, int y);

    /*
    *   Retorna cada unidad que hay en el mapa
    */
    std::vector<UnitDTO*> getUnits();

    /*
    *   Retorna cada edificio que hay en el mapa
    */
    std::vector<BuildingDTO*> getBuildings();

    /*
    *   Al player de id le asigna una unidad del type en posicion x,y
    */
    void putUnit(InstanceId id_player, char type, int x, int y);

    /*
    *   Le asigna una building al player del type en la pos x,y
    */
    void putBuilding(char type, int x, int y);


    Building* getBuilding(char type, int x, int y);

    Unit* getUnit(char type, int x, int y);










    //-----------------------------------//
    void setDestiny(Unit& unit, int x_dest, int y_dest);

    Attackable * getClosestAttackable(Position &position, int limitRadius, Player& player);

    bool canMove(Unit& unit, Position pos);

    Unit* getUnit(char type);

    void occupy(Building* building);
    void free(Building& building);


    ConstructionCenter *getConstructionCenterFor(InstanceId i);
};

#endif //__MAP_H__