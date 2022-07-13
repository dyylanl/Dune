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
    map.putUnit(id_player, unit_type,5*(int)id_player, 5*(int)id_player);
}

void Model::addPlayer(InstanceId player_id) {
    current_players += 1;
    //ConstructionCenter* center = map.getConstructionCenterFor(player_id);
    //ConstructionCenter* center = map.getConstructionCenterFor(player_id);
    Player player(player_id, map.getConstructionCenterFor(player_id));
    players.emplace(player_id, std::move(player));
}

void Model::deletePlayer(InstanceId player_id) {
    players.erase(player_id);
    current_players -= 1;
}

void Model::selectUnit(InstanceId player, int x, int y) {
    map.selectUnit(player,x,y);
}

void Model::moveUnit(InstanceId player, int x, int y) {
    std::cout << "Jugador: " << player << " moviendo unidad a la posicion " << x << "," << y << std::endl;
}



Harvester& Model::createHarvester(int x, int y, int player) {
    Harvester* harvester = new Harvester(x, y);
    return *harvester;
}

HeavyInfantry& Model::createHeavyInfantry(int x, int y, int player) {
    HeavyInfantry* heavyInfantry = new HeavyInfantry(x, y);
    return *heavyInfantry;
}

LightInfantry& Model::createLightInfantry(int x, int y, int player) {
    LightInfantry* lightInfantry = new LightInfantry(x, y);
    return *lightInfantry;
}

Raider& Model::createRaider(int x, int y, int player) {
    Raider* raider = new Raider(x, y);
    return (*raider);
}

Tank& Model::createTank(int x, int y, int player) {
    Tank* tank = new Tank(x, y);
    return *tank;
}

Trike& Model::createTrike(int x, int y, int player) {
    Trike* trike = new Trike(x, y);
    return *trike;
}

// Se deben crear las vistas de cada edificio (o la fabrica de vistas para los edificios)
Barracks& Model::createBarracks(int x, int y, int player) {
    Position pos(x, y);
    Barracks* building = new Barracks(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

ConstructionCenter& Model::createConstructionCenter(int x, int y, int player) {
    Position pos(x, y);
    ConstructionCenter* building = new ConstructionCenter(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

HeavyFactory& Model::createHeavyFactory(int x, int y, int player) {
    Position pos(x, y);
    HeavyFactory* building = new HeavyFactory(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

LightFactory& Model::createLightFactory(int x, int y, int player) {
    Position pos(x, y);
    LightFactory* building = new LightFactory(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

Refinery& Model::createSpiceRefinery(int x, int y, int player) {
    Position pos(x, y);
    Refinery* building = new Refinery(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

Silo& Model::createSpiceSilo(int x, int y, int player) {
    Position pos(x, y);
    Silo* building = new Silo(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

WindTrap& Model::createWindTrap(int x, int y, int player) {
    Position pos(x, y);
    WindTrap* building = new WindTrap(pos.x, pos.y, map.getBlockWidth(), map.getBlockHeight());
    return *(building);
}

void Model::actionOnPosition(Position &pos, Unit &unit) {
    unit.actionOnPosition(map, pos);
}

bool Model::canWeBuild(Position& pos, int width, int height, int cost, Player& player) {
    if ( cost > player.gold ) {
        return false;
    }
    return false;
}

int Model::numberOfPlayers() {
    return players.size();
}
