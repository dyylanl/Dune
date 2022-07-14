#ifndef DUNE_MODEL_H
#define DUNE_MODEL_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "../../config/ConfigReader.h"
#include "Units/Harvester.h"
#include "Units/HeavyInfantry.h"
#include "Units/LightInfantry.h"
#include "Units/Tank.h"
#include "Units/Raider.h"
#include "Units/Trike.h"
#include "Buildings/Barrack.h"
#include "Buildings/HeavyFactory.h"
#include "Buildings/LightFactory.h"
#include "Buildings/Silo.h"
#include "Buildings/WindTrap.h"

class Model {
private:
    std::map<InstanceId,Player> players;
    Map map;
    Id map_id;
    int current_players;
    int max_players;
    bool finished;
    ConfigurationReader& config;
public:
    /*
    *   Recibe por parametro la ruta del mapa que se usara en la partida
    */
    Model(ConfigurationReader& config, const std::string& path_to_map_config);

    /*
    *   Retorna la cantidad de jugadores requeridas para la partida actual
    */
    int getMaxPlayers();

    /*
    *   Retorna la cantidad de jugadores ACTUALES
    */
    int getCurrentPlayers();

    /*
    *   Retorna el terreno del mapa en char para ser enviado
    */
    std::vector<std::vector<char>>& getMap();

    /*
    *   Retorna un vector de edificios dtos para ser enviados
    */
    std::vector<BuildingDTO*> getBuildings();

    /*
    *   Retorna un vector de unidades dtos para ser enviado
    */
    std::vector<UnitDTO*> getUnits();

    /*
    *   Agrega un jugador a la partida
    */
    void addPlayer(InstanceId player_id);

    /*
    *   Elimina un jugador de la partida
    */
    void deletePlayer(InstanceId player_id);


    // --------- COMANDOS ---------- //

    /*
    *   Selecciona una unidad si le pertenece al player
    */
    void selectUnit(InstanceId player, int x, int y);

    /*
    *   Mueve todas las unidades seleccionadas por el jugador
    */
    void moveUnit(InstanceId player, int x, int y); // posicion destino

    /*
    *   Construye un edificio del tipo y posicion indicado si el player tiene los recursos necesarios
    */
    void buildBuilding(InstanceId player, char build_type, int x, int y);

    void putUnit(InstanceId player, char unit_type);

    Harvester& createHarvester(int x, int y, int player);

    HeavyInfantry& createHeavyInfantry(int x, int y, int player);

    LightInfantry& createLightInfantry(int x, int y, int player);

    Raider& createRaider(int x, int y, int player);

    Tank& createTank(int x, int y, int player);

    Trike& createTrike(int x, int y, int player);

    Barracks& createBarracks(int x, int y, int player);

    ConstructionCenter& createConstructionCenter(int x, int y, int player);

    HeavyFactory& createHeavyFactory(int x, int y, int player);

    LightFactory& createLightFactory(int x, int y, int player);

    Refinery& createSpiceRefinery(int x, int y, int player);

    Silo& createSpiceSilo(int x, int y, int player);

    WindTrap& createWindTrap(int x, int y, int player);

    void actionOnPosition(Position &pos, Unit &unit);

    bool canWeBuild(Position& pos, int width, int height, int cost, Player& player);

    int numberOfPlayers();

    void moveUnits(int it);

};

#endif //DUNE_MODEL_H
