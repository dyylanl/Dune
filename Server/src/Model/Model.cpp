#include "../../includes/Model/Model.h"

Model::Model(ConfigurationReader& config1, const std::string& map_path) :
        map(map_path),
        current_players(0),
        max_players(map.getMaxPlayers()),
        finished(false),
        config(config1)
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

std::vector<BuildingDTO*> Model::getBuildings() {
    return map.getBuildings();
}

std::vector<UnitDTO*> Model::getUnits() {
    return map.getUnits();
}

void Model::buildBuilding(InstanceId id_player, char build_type, int x, int y) {
    map.putBuilding(build_type,x,y);
}

void Model::putUnit(InstanceId id_player, char unit_type) {
    map.putUnit(players.at(id_player).getBarrackPosition(), unit_type);
}

void Model::addPlayer(InstanceId player_id) {
    current_players += 1;
    std::cout << "[MODEL]: Jugador agregado" << std::endl;
    //ConstructionCenter* center = map.getConstructionCenterFor(player_id);
    //Player player(player_id, *center);
    //players[player_id] = player;
}

void Model::deletePlayer(InstanceId player_id) {
    players.erase(player_id);
    current_players -= 1;
}

void Model::selectUnit(InstanceId player, int x, int y) {
    std::cout << "Jugador: " << player << " selecciona unidad en " << x << "," << y << std::endl;
}

void Model::moveUnit(InstanceId player, int x, int y) {
    std::cout << "Jugador: " << player << " moviendo unidad a la posicion " << x << "," << y << std::endl;
}
