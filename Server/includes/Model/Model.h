#ifndef DUNE_MODEL_H
#define DUNE_MODEL_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "../../config/ConfigReader.h"

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

};

#endif //DUNE_MODEL_H
