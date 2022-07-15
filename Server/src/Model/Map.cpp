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
                            buildings(),
                            units()
{
    std::vector <std::vector<Terrain>> terrain_init((uint16_t) rows, std::vector<Terrain>((uint16_t) cols, Terrain('A')));
    std::vector <std::vector<int>> spice_init((uint16_t) rows, std::vector<int>((uint16_t) cols, 0));
    this->terrains = terrain_init;
    spice_init = map_reader.getSpice();
    int rows_ = mapa.size();
    int cols_ = mapa[0].size();

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            char type = this->mapa[j][i];
            terrains[i][j] = Terrain(type);
            terrains[i][j].setSpice(spice_init[i][j]);
        }
    }
    int total_buildings = map_reader.getTotalBuildings();
    for (int i = 0; i < total_buildings; ++i) {
        auto* construction_center = map_reader.getConstructionCenterFor((InstanceId)i);
        buildings.push_back(construction_center);
        centers.emplace(i, construction_center);
        occupy(construction_center);
    }
}

char Map::getTypeTerrain(int posX, int posY) {
    return this->terrains[posX][posY].getKey();
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
    return reinterpret_cast<Terrain &>(this->terrains[x][y]);
}

Terrain& Map::at(const Position& pos) {
    return reinterpret_cast<Terrain &>(this->terrains[pos.getX()][pos.getY()]);
}

bool Map::isValid(Position pos) {
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

std::vector<UnitDTO*> Map::getUnits() {
    std::vector<UnitDTO*> retUnitsDto = {};
    if (units.empty()) {
        return retUnitsDto;
    }
    for (auto &unit : units) {
        auto* dto = new UnitDTO(1,1, // por que el cliente necesita los id's?
                                unit->getPosition().getX(),unit->getPosition().getY(),
                                unit->getNextPosition().getX(),unit->getNextPosition().getY(),
                                unit->getType(),unit->getLife(),0);
        if (unit->isSelected()) {
            dto->selected = 1;
        } else {
            dto->selected = 0;
        }
        retUnitsDto.push_back(dto);
    }
    return retUnitsDto;
}
 
std::vector<BuildingDTO*> Map::getBuildings() {
    std::vector<BuildingDTO*> retBuildingsDto;
    for (auto &build : buildings) {
        auto* dto = new BuildingDTO(1, 1, // por que el cliente necesita los id's?
        build->getPosition().getX(),build->getPosition().getY(),
        build->getType(),build->getLife());
        retBuildingsDto.push_back(dto);
    }
    return retBuildingsDto;
}

Building* Map::getBuilding(char type, int x, int y) {
    switch (type) {
        case BARRACKS_KEY:
            return new Barracks(x,y,GameConfiguration::getConfig().barracksWidth,GameConfiguration::getConfig().barracksHeight);
        case HEAVY_FACTORY_KEY:
            return new HeavyFactory(x,y,GameConfiguration::getConfig().heavyFactoryWidth,GameConfiguration::getConfig().heavyFactoryHeight);
        case LIGHT_FACTORY_KEY:
            return new LightFactory(x,y,GameConfiguration::getConfig().lightFactoryWidth,GameConfiguration::getConfig().lightFactoryHeight);
        case REFINERY_KEY:
            return new Refinery(x,y,GameConfiguration::getConfig().refineryWidth,GameConfiguration::getConfig().refineryHeight);
        case SILO_KEY:
            return new Silo(x,y,GameConfiguration::getConfig().siloWidth,GameConfiguration::getConfig().siloHeight);
        case WIND_TRAP_KEY:
            return new WindTrap(x,y,GameConfiguration::getConfig().windTrapWidth,GameConfiguration::getConfig().windTrapHeight);
        case PALACE_KEY:
            return new Palace(x,y,GameConfiguration::getConfig().palaceWidth,GameConfiguration::getConfig().palaceHeight);
        default: throw Exception("Invalid get build.\n");
    }
}

void Map::putUnit(InstanceId id_player, char type, int x, int y) {
    Position pos(x,y);
    pos.normalize();
    Unit* unit = getUnit(type,pos.getX(),pos.getY(), id_player);
    units.push_back(unit);
    this->at(pos).occupy();
}

void Map::putBuilding(char type, int x, int y) {
    Position pos(x,y);
    pos.normalize();
    Building* build = getBuilding(type,pos.x,pos.y);
    if (canWeBuild(pos,build->width,build->height)) {
        buildings.push_back(build);
        occupy(build);
    }
}

Map::~Map() {
    if (!units.empty()) {
        for (Unit* unit : units) {
            delete unit;
        }
    }
    for (Building* build : buildings) {
        delete build;
    }
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
            this->at(building.getPosition().x + j, building.getPosition().y + i).free();
        }
    }
}

void Map::occupy(Building* building) {
    for (int i = 0; i < building->height; i++) {
        for (int j = 0; j < building->width; j++) {
            this->at(building->getPosition().y + j, building->getPosition().x + i).buildOn(building);
        }
    }
}

Unit *Map::getUnit(char type, int x, int y, int player_id) {
    switch (type) {
        case LIGHT_INFANTRY_KEY: return new LightInfantry(x,y,player_id);
        case HEAVY_INFANTRY_KEY: return new HeavyInfantry(x,y,player_id);
        case HARVESTER_KEY: return new Harvester(x,y,player_id);
        case TRIKE_KEY: return new Trike(x,y,player_id);
        case RAIDER_KEY: return new Raider(x,y,player_id);
        case TANK_KEY: return new Tank(x,y,player_id);
        default: throw Exception("Invalid get unit type");
    }
}

ConstructionCenter *Map::getConstructionCenterFor(InstanceId player_id) {
    return this->centers.at(player_id);
}

void Map::selectUnit(InstanceId player_id, int x, int y) {
    Position pos(x,y);
    pos.normalize();
    for (auto& unit : units) {
        if (pos.getX() == unit->getPosition().getX() && pos.getY() == unit->getPosition().getY()) {
            if (unit->player_id == (int)player_id) {
                unit->select();
            }
        }
    }
}

bool Map::canWeBuild(Position pos, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Position current_pos(pos.getY() + i, pos.getX() + j);
            if (isValid(current_pos)) {
                if ((terrains[current_pos.getX()][current_pos.getY()].getKey() != ROCK_KEY) || this->at(current_pos).isOccupied()) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
    return true;
}

void Map::moveUnit(InstanceId player, int x, int y) {
    Position pos(x,y);
    pos.normalize();
    if (isValid(pos)) {
        for (auto& unit : units) {
            if (unit->player_id == (int)player) {
                if (unit->isSelected()) {
                    if (canMove(*unit,pos)) {
                        setDestiny(*unit,pos.getX(),pos.getY());
                    }
                }
            }
        }
    }
}

void Map::moveUnits(int it) {
    if (units.empty()) {
        return;
    }
    for (auto &unit : units) {
        if (unit->isSelected()) {
            unit->move(*this);
        }
    }
}
