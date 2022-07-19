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

std::vector<BuildingDTO> Model::getBuildings() {
    return map.getBuildings();
}

std::vector<UnitDTO> Model::getUnits() {
    return map.getUnits();
}

void Model::buildBuilding(InstanceId id_player, char build_type, int x, int y) {
    Position pos(x,y);
    pos.normalize();
    int gold = players.at(id_player).gold;
    int energy = players.at(id_player).generatedEnergy;
    Building* build = map.getBuilding(id_player, build_type,pos.getX(),pos.getY());
    int gold_req = build->cost;
    int energy_req = build->energy;
    if (gold >= gold_req && energy >= energy_req) {
        if (map.canWeBuild(pos, build->width, build->height)) {
            players.at(id_player).addBuilding(build);
            map.putBuilding(build);
        }
    }
}

void Model::putUnit(InstanceId id_player, char unit_type) {
    if (players.at(id_player).canTrainUnits()) {
        Unit* unit = map.getUnit(unit_type,players.at(id_player).getBarrackPosition().getX(),players.at(id_player).getBarrackPosition().getY(), id_player);
        int gold = players.at(id_player).gold;
        int gold_req = unit->getCost();
        if (gold >= gold_req) {
            players.at(id_player).addUnit(unit);
            map.putUnit(unit);
        }
    }
}

void Model::addPlayer(InstanceId player_id) {
    current_players += 1;
    Player player(player_id, map.getConstructionCenterFor(player_id));
    players.emplace(player_id, std::move(player));
}

void Model::deletePlayer(InstanceId player_id) {
    players.at(player_id).cleanDeads();
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

int Model::numberOfPlayers() {
    return players.size();
}

std::vector<PlayerDTO> Model::getPlayers() {
    std::vector<PlayerDTO> players_ret;
    for (auto& [id,player] : players) {
        auto dto = PlayerDTO(id, player.gold, player.generatedEnergy, player.status);
        players_ret.push_back(dto);
    }
    return players_ret;
}


void Model::updateModel() {
    map.moveUnits();
    map.updateMap();
    for (auto [id,player] : players) {
        player.cleanDeads();
        if (current_players == 1 && (!player.isDefeated())){
            player.status = 1;
            finished = true;
        }
    }
}

Position Model::getInitialPosition(InstanceId player_id) {
    return players.at(player_id).getConstructionCenter()->getPosition();
}