#include "../../includes/Model/Model.h"

Model::Model(const std::string& map_path) :
        map(map_path),
        current_players(0),
        max_players(map.getMaxPlayers()),
        finished(false)
{

}

int Model::getMaxPlayers() {
    return max_players;
}

int Model::getCurrentPlayers() {
    return current_players;
}

std::vector<std::vector<char>> &Model::getMap() {
    return map.getMap();
}

std::vector<BuildingDTO> Model::getBuildings() {
    return map.getBuildings();
}

void Model::putBuilding(InstanceId id_player, char build_type, int x, int y) {
    map.putBuilding(build_type,x,y);
}

void Model::putUnit(InstanceId id_player, char unit_type) {
    map.putUnit(players.at(id_player).getBarrackPosition(), unit_type);
}

void Model::addPlayer(InstanceId player_id) {
    current_players += 1;
    //players.at(player_id) = Player(player_id,ConstructionCenter());
}
