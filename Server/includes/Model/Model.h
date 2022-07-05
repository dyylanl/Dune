#ifndef DUNE_MODEL_H
#define DUNE_MODEL_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"

class Model {
private:
    std::map<InstanceId,Player> players;
    Map map;
    Id map_id;
    int current_players;
    int max_players;
    bool finished;
public:
    /*
    *   Recibe por parametro la ruta del mapa que se usara en la partida
    */
    Model(const std::string& path_to_map_config);
    int getMaxPlayers();
    int getCurrentPlayers();

    std::vector<std::vector<char>>& getMap();

    void putBuilding(InstanceId id_player, char build_type, int x, int y);
    std::vector<BuildingDTO> getBuildings();

    void putUnit(InstanceId id_player, char unit_type);

    void addPlayer(InstanceId player_id);

};

#endif //DUNE_MODEL_H
