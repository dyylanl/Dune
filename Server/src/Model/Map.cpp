#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"
#include "../../includes/Model/Terrains/Rock.h"




Map::~Map() {}

bool Map::canMove(const Unit& unit, Position position) {
    return (isValid(position) && canMove(unit,position));
}

char Map::getTypeTerrain(int posX, int posY) {
    return this->terrrains[posX][posY].getKey();
}

void Map::selectUnit(int pos_x, int pos_y) {
    std::cout << "Seleccionando unidad en posicion " << pos_x << "," << pos_y << std::endl;
}

bool Map::hasNews(){
    return this->news;
}

void Map::updateSpice(int x, int y){
    std::cout << "Volviendo a cargar la especia" << std::endl;
}

void Map::getInitialPositions() {
    std::cout << "Leyendo del yaml para cargar los centros de construcciones de cada jugador" << std::endl;
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

Terrain& Map::blockAt(int x, int y) {
    return reinterpret_cast<Terrain &>(this->terrrains[x][y]);
}

Terrain& Map::at(const Position& pos) {
    return reinterpret_cast<Terrain &>(this->terrrains[pos.getX()][pos.getY()]);
}

bool Map::isValid(Position &pos) {
    return pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < rows && pos.getY() < cols;
}

void Map::put(Unit &unit) {
    units.push_back(&unit);
    this->at(unit.getPosition()).occupy();
}

void Map::put(Building* building) {
    buildings.push_back(building);
    this->occupy(building);
}

void Map::occupy(Building* building) {
    for (int i = 0; i < building->height; i++) {
        for (int j = 0; j < building->width; j++) {
            this->terrrains[building->getPosition().x+i][building->getPosition().y+j].buildOn(building);
        }
    }
}

bool Map::canMove(Unit& unit, Position pos) {
    return unit.canMoveAboveTerrain(this->at(pos)) && !this->at(pos).isOccupied();
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

Unit* Map::getClosestUnit(Position pos, int limitRadius, Player& player) {
    Unit* closest_unit = nullptr;
    int closest_unit_distance = limitRadius;
    for (auto& current_unit : units) {
        int distance = current_unit->getPosition().sqrtDistance(pos);
        if (distance < limitRadius && distance < closest_unit_distance) {
            closest_unit = current_unit;
            closest_unit_distance = distance;
        }
    }
    return closest_unit;
}

std::vector<Unit*> Map::getUnitsInArea(Area& area, Player& player) {
    std::vector<Unit*> answer;
    for (auto& unit : units) {
        if (unit->getPosition().x > area.getX())
            if (unit->getPosition().x < area.getX() + area.getWidth())
                if (unit->getPosition().y > area.getY())
                    if (unit->getPosition().y < area.getY() + area.getHeight())
                        answer.emplace_back(unit);
    }
    if (answer.empty()) {
        Unit* unit = getClosestUnit(Position(area.getX() + area.getWidth(), area.getY() + area.getHeight()), 120, player);
        if (unit != nullptr)
            answer.emplace_back(unit);
    }
    return (answer);
}

std::vector<Unit*> Map::getUnitsInArea(Area& area) {
    std::vector<Unit*> answer;
    for (auto& unit : units) {
        if (unit->getPosition().x > area.getX())
            if (unit->getPosition().x < area.getX() + area.getWidth())
                if (unit->getPosition().y > area.getY())
                    if (unit->getPosition().y < area.getY() + area.getHeight())
                        answer.emplace_back(unit);
    }
    return (answer);
}

std::vector<Building*> Map::getBuildingsInArea(Area& area, Player& player) {
    std::vector<Building*> answer;
    Position pos(area.getX() + area.getWidth(), area.getY() + area.getHeight());
    for (auto& building : buildings) {
        if ( (building->getPosition().x > area.getX()) &&(building->getPosition().x + building->width < area.getX() + area.getWidth()) &&(building->getPosition().y > area.getY()) &&(building->getPosition().y + building->height < area.getY() + area.getHeight())) {
                answer.emplace_back(building);
            } else {
                if ((pos.x > building->getPosition().x) && (pos.x < building->getPosition().x + building->width) &&
                    (pos.y > building->getPosition().y) && (pos.y < building->getPosition().y + building->height)) {
                    answer.emplace_back(building);
                }
            }
    }
    return (answer);
}

std::vector<Building*> Map::getBuildingsInArea(Area& area) {
    std::vector<Building*> answer;
    Position pos(area.getX() + area.getWidth(), area.getY() + area.getHeight());
    Position areaCenter(area.getX() + area.getWidth() / 2, area.getY() + area.getHeight() / 2);
    for (auto& building : buildings) {
        if ( (building->getClosestPosition(areaCenter).x > area.getX()) &&
             (building->getClosestPosition(areaCenter).x + building->width < area.getX() + area.getWidth()) &&
             (building->getClosestPosition(areaCenter).y > area.getY()) &&
             (building->getClosestPosition(areaCenter).y + building->height < area.getY() + area.getHeight())) {
            answer.emplace_back(building);
        } else {
            if ((pos.x > building->getClosestPosition(areaCenter).x) && (pos.x < building->getClosestPosition(areaCenter).x + building->width) &&
                (pos.y > building->getClosestPosition(areaCenter).y) && (pos.y < building->getClosestPosition(areaCenter).y + building->height)) {
                answer.emplace_back(building);
            }
        }
    }
    return (answer);
}

void Map::cleanUnit(Unit *unit) {
    this->at(unit->getPosition()).free();
    units.erase(std::find(units.begin(), units.end(), unit));
}

void Map::cleanBuilding(Building *building) {
    this->free(*building);
    buildings.erase(std::find(buildings.begin(), buildings.end(), building));
}

void Map::free(Building &building) {
    for (int i = 0; i < building.height; i++) {
        for (int j = 0; j < building.width; j++) {
            this->at(building.getPosition().x + i, building.getPosition().y + j).free();
        }
    }
}

bool Map::canWeBuild(Position& pos, int width, int height, Player& player) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Position aux(pos.getX() + i, pos.getY() + j);
            if (isValid(aux)) {
                if ((this->at(aux).getKey() != Rock().getKey()) || this->at(aux).isOccupied()) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    for (int i = -5; i <= height + 5; i++) {
        for (int j = -5; j <= width + 5; j++) {
            Position aux(pos.getX() + i, pos.getY() + j);
            if (isValid(aux)) {
                if (this->at(aux).isBuiltOn()) {
                }
            }
        }
    }

    return false;
}

Position Map::getClosestFreePosition(Building* building) {
    int dist = 1;
    bool found = false;
    Position& pos = building->getPosition();
    while (!found) {
        for (int i = - dist; i <= building->height + dist; i++) {
            for (int j =  - dist; j <= building->width + dist; j++) {
                try {
                    if (!(this->at(pos.x + i, pos.y + j).isOccupied())) {
                        return {pos.x + i, pos.y + j};
                    }
                }
                catch (std::out_of_range& e) {}
            }
        }
        dist += 1;
    }
    return pos;
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
        if (distance < limitRadius
            && distance < closest_unit_distance) {
            closest_attackable = current_building;
            closest_unit_distance = distance;
        }
    }
    return closest_attackable;
}
/*
Position Map::getCornerPosition(Position& pos) {
    return {(pos.x / BLOCK_WIDTH) * BLOCK_WIDTH, (pos.y / BLOCK_HEIGHT) * BLOCK_HEIGHT};
}*/

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
                     && this->blockAt(cur_pos_x, cur_pos_y).hasFarm()) {
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

Map::Map(std::string config_path) : 
                            map_reader(config_path),
                            rows(map_reader.getRows()),
                            cols(map_reader.getCols()),
                            mapa(map_reader.getMap())
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
    std::cout << "Se inicio un mapa cargado en: " << config_path << std::endl;
}