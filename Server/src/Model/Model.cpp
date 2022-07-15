#include "../../includes/Model/Model.h"
#include "../../../Common/includes/Exceptions/Exception.h"

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
    int gold = players.at(id_player).gold;
    int energy = players.at(id_player).generatedEnergy;
    Building* build = map.getBuilding(build_type,x,y);
    int gold_req = build->cost;
    int energy_req = build->energy;
    if (gold >= gold_req && energy >= energy_req) {
        players.at(id_player).subGold(gold_req);
        players.at(id_player).generatedEnergy -= energy_req;
        players.at(id_player).addBuilding(build);
        map.putBuilding(build_type,x,y);
    }
    delete build;
}

void Model::putUnit(InstanceId id_player, char unit_type) {
    if (players.at(id_player).canTrainUnits()) {
        int gold = players.at(id_player).gold;
        Unit* unit = map.getUnit(unit_type,1,1, id_player);
        int gold_req = unit->getCost();
        if (gold >= gold_req) {
            players.at(id_player).subGold(gold_req);
            map.putUnit(id_player, unit_type, players.at(id_player).getBarrackPosition().getX(), players.at(id_player).getBarrackPosition().getY());
        }
        delete unit;
    }
}

void Model::addPlayer(InstanceId player_id) {
    current_players += 1;
    Player player(player_id, map.getConstructionCenterFor(player_id));
    players.emplace(player_id, std::move(player));
}

void Model::deletePlayer(InstanceId player_id) {
    players.at(player_id).clean();
    players.erase(player_id);
    current_players -= 1;
}

void Model::selectUnit(InstanceId player, int x, int y) {
    map.selectUnit(player,x,y);
}

void Model::moveUnit(InstanceId player, int x, int y) {
    map.moveUnit(player,x,y);
}

void Model::actionOnPosition(Position &pos, Unit &unit) {
    unit.actionOnPosition(map, pos);
}

int Model::numberOfPlayers() {
    return players.size();
}

void Model::moveUnits(int it) {
    map.moveUnits(it);
}

std::vector<PlayerDTO*> Model::getPlayers() {
    std::vector<PlayerDTO*> players_ret;
    for (auto& [id,player] : players) {
        auto* dto = new PlayerDTO(id, player.gold, player.generatedEnergy);
        players_ret.push_back(dto);
    }
    return players_ret;
}


