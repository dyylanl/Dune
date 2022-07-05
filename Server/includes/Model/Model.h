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
    int getMaxPlayers();
    int getCurrentPlayers();
    std::vector<std::vector<char>>& getMap();
    std::vector<BuildingDTO*> getBuildings();
    std::vector<UnitDTO*> getUnits();
    void addPlayer(InstanceId player_id);
    void deletePlayer(InstanceId player_id);
    // --------- COMANDOS ---------- //
    void selectUnit(InstanceId player, int x, int y);
    void moveUnit(InstanceId player, int x, int y); // posicion destino
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
};

#endif //DUNE_MODEL_H
