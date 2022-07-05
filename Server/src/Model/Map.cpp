#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"
#include "../../includes/Model/Terrains/Rock.h"
#include "../../includes/Model/Buildings/Barrack.h"
#include "../../includes/Model/Buildings/HeavyFactory.h"
#include "../../includes/Model/Buildings/LightFactory.h"
#include "../../includes/Model/Buildings/Refinery.h"
#include "../../includes/Model/Buildings/Silo.h"
#include "../../includes/Model/Buildings/WindTrap.h"
#include "../../includes/Model/Buildings/Palace.h"
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../includes/Model/Units/LightInfantry.h"
#include "../../includes/Model/Units/HeavyInfantry.h"
#include "../../includes/Model/Units/Harvester.h"
#include "../../includes/Model/Units/Trike.h"
#include "../../includes/Model/Units/Raider.h"
#include "../../includes/Model/Units/Tank.h"


Map::Map(std::string map_path) :
                            map_reader(map_path),
                            rows(map_reader.getRows()),
                            cols(map_reader.getCols()),
                            max_players(map_reader.getReqPlayers()),
                            mapa(map_reader.getMap()),
                            buildingsDTO(),
                            buildings()
{
    std::vector <std::vector<Terrain>> terrain_init((uint16_t) rows, std::vector<Terrain>((uint16_t) cols, Terrain('A')));
    this->terrrains = terrain_init;
    int rows_ = mapa.size();
    int cols_ = mapa[0].size();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            char type = this->mapa[i][j];
            terrrains[i][j] = Terrain(type);
        }
    }
    int total_buildings = map_reader.getTotalBuildings();
    for (int i = 0; i < total_buildings; ++i) {
        auto* construction_center = map_reader.getConstructionCenterFor((InstanceId)i);
        buildings.push_back(construction_center);
        BuildingDTO centerDto;
        centerDto.type = CONSTRUCTION_CENTER_KEY;
        centerDto.life = construction_center->getLife();
        centerDto.pos_x = construction_center->getPosition().x*BLOCK_WIDTH;
        centerDto.pos_y = construction_center->getPosition().y*BLOCK_HEIGHT;
        buildingsDTO.push_back(centerDto);

    }
}

char Map::getTypeTerrain(int posX, int posY) {
    return this->terrrains[posX][posY].getKey();
}

void Map::updateSpice(int x, int y){
    std::cout << "Volviendo a cargar la especia" << std::endl;
}

int Map::getWidth() {
    return cols;
}

int Map::getHeight() {
    return rows;
}

int Map::getBlockWidth() {
    return BLOCK_WIDTH;
}

int Map::getBlockHeight() {
    return BLOCK_HEIGHT;
}

int Map::getWidthInBlocks() {
    return cols;
}

int Map::getHeightInBlocks() {
    return rows;
}

Terrain& Map::at(int x, int y) {
    if ((x < 0) || (y < 0)) {
        throw std::out_of_range("Out of range");
    }
    return reinterpret_cast<Terrain &>(this->terrrains[x][y]);
}

Terrain& Map::at(const Position& pos) {
    return reinterpret_cast<Terrain &>(this->terrrains[pos.getX()][pos.getY()]);
}

bool Map::isValid(Position &pos) {
    return (pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < rows && pos.getY() < cols);
}

Position Map::getClosestSpeciaPosition(Position pos, int radius) {
    int block_x = (pos.x);
    int block_y = (pos.y);
    int min_distance = radius + 1;
    Position min_position = pos;
    for (int i = -radius; i <= +radius; ++i) {
        for (int j = -(radius - abs(i)); j <= +(radius - abs(i)); ++j) {
            int cur_pos_x = (block_x + j);
            int cur_pos_y = (block_y + i);
            if ((cur_pos_y + j) >= 0 &&
                (cur_pos_y + j) < cols &&
                (cur_pos_x + i) >= 0 &&
                (cur_pos_x + i) < rows) {
                if ( abs(i) + abs(j) < min_distance
                     && this->at(cur_pos_x, cur_pos_y).hasFarm()) {
                    min_distance = abs(i) + abs(j);
                    min_position = Position(cur_pos_x, cur_pos_y);
                }
            }
        }
    }
    return min_position;
}

int Map::getSpeedFactorAt(Position &pos) {
    return this->at(pos).getSpeedFactor();
}

std::vector<std::vector<char>> &Map::getMap() {
    return this->mapa;
}

std::vector<UnitDTO> Map::getUnits() {
    return unitsDTO;
}
 
std::vector<BuildingDTO> Map::getBuildings() {
    return buildingsDTO;
}

Building* Map::getBuilding(char type, int x, int y) {
    switch (type) {
        case BARRACKS_KEY:
            return new Barracks(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        case HEAVY_FACTORY_KEY:
            return new HeavyFactory(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        case LIGHT_FACTORY_KEY:
            return new LightFactory(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        case REFINERY_KEY:
            return new Refinery(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        case SILO_KEY:
            return new Silo(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        case WIND_TRAP_KEY:
            return new WindTrap(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        case PALACE_KEY:
            return new Palace(x,y,BLOCK_WIDTH,BLOCK_HEIGHT);
        default: throw Exception("Invalid get build.\n");
    }
}

void Map::putUnit(InstanceId id_player, char type, int x, int y) {
    UnitDTO unit;
    unit.type = type;
    unit.pos_x = x;
    unit.pos_y = y;
    unit.unit_id = id_player;
    unitsDTO.push_back(unit);
}
// todo: usar la clase building
void Map::putBuilding(char type, int x, int y) {
    Position pos(x,y);
    pos.normalize();
    if (!isValid(pos)) {
        std::cout << "Poner construccion en posicion invalida: " << pos.x << "," << pos.y << std::endl;
        return;
    }
    Building* build = getBuilding(type,x,y);
    buildings.push_back(build);
    BuildingDTO buildDTO;
    buildDTO.type = type;
    buildDTO.pos_x = x;
    buildDTO.pos_y = y;
    buildingsDTO.push_back(buildDTO);
}

Map::~Map() {
    for (auto* unit : units) {
        delete unit;
    }
    for (auto* build : buildings) {
        delete build;
    }
}

void Map::putUnit(Position pos, char unit_type) {
    pos.normalize();
    if (isValid(pos)) {
        std::cout << "Poner unidad en posicion invalida: " << pos.x << "," << pos.y << std::endl;
        return;
    }
    Unit* unit = getUnit(unit_type, pos.x, pos.y);
    units.push_back(unit);
    UnitDTO unit1{};
    unit1.type = unit_type;
    unit1.pos_x = pos.x;
    unit1.pos_y = pos.y;
    unitsDTO.push_back(unit1);
}

ConstructionCenter* Map::getConstructionCenterFor(InstanceId player_id) {
    return map_reader.getConstructionCenterFor(player_id);
}

void Map::loadConstructionsCenter() {

}

void Map::setDestiny(Unit &unit, int x_dest, int y_dest) {
    AStar algorithm(*this);
    Position p_destiny(x_dest, y_dest);
    std::stack<Position> path = algorithm.makePath(unit, p_destiny);
    if (!path.empty()) {
        this->at(unit.getPosition()).free();
    }
    unit.setPath(path, p_destiny);
}

Attackable *Map::getClosestAttackable(Position &position, int limitRadius, Player& player) {
    Attackable* closest_attackable = nullptr;
    int closest_unit_distance = limitRadius;
    for (auto& current_unit : units) {
        int distance = current_unit->getPosition().sqrtDistance(position);
        if ((distance < limitRadius) && (distance < closest_unit_distance)) {
            closest_attackable = current_unit;
            closest_unit_distance = distance;
        }
    }
    for (auto& current_building : buildings) {
        Position& pos = current_building->getClosestPosition(position);
        int distance = pos.sqrtDistance(position);
        if (distance < limitRadius && distance < closest_unit_distance) {
            closest_attackable = current_building;
            closest_unit_distance = distance;
        }
    }
    return closest_attackable;
}

bool Map::canMove(Unit& unit, Position pos) {
    return unit.canMoveAboveTerrain(this->at(pos)) && !this->at(pos).isOccupied();
}

void Map::free(Building &building) {
    for (int i = 0; i < building.height; i++) {
        for (int j = 0; j < building.width; j++) {
            this->at(building.getPosition().x + j * BLOCK_WIDTH, building.getPosition().y + i * BLOCK_HEIGHT).free();
        }
    }
}

void Map::occupy(Building* building) {
    for (int i = 0; i < building->height; i++) {
        for (int j = 0; j < building->width; j++) {
            this->at(building->getPosition().x + j, building->getPosition().y + i).buildOn(building);
        }
    }
}

Unit *Map::getUnit(char type, int x, int y) {
    switch (type) {
        case LIGHT_INFANTRY_KEY: return new LightInfantry(x,y);
        case HEAVY_INFANTRY_KEY: return new HeavyInfantry(x,y);
        case HARVESTER_KEY: return new Harvester(x,y);
        case TRIKE_KEY: return new Trike(x,y);
        case RAIDER_KEY: return new Raider(x,y);
        case TANK_KEY: return new Tank(x,y);
        default: throw Exception("Invalid get unit type");
    }
}

