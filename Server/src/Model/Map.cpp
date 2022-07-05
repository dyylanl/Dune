#include <algorithm>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"
#include "../../includes/Model/Terrains/Rock.h"


Map::Map(std::string map_path) :
                            map_reader(map_path),
                            rows(map_reader.getRows()),
                            cols(map_reader.getCols()),
                            max_players(map_reader.getReqPlayers()),
                            mapa(map_reader.getMap()),
                            buildingsDTO(map_reader.getBuildings())
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
    std::cout << "[MAP]: Map path: " << map_path << std::endl;
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
    BuildingDTO build;
    //build.build_id = id_player;
    build.type = type;
    build.pos_x = x;
    build.pos_y = y;
    buildingsDTO.push_back(build);
}

Map::~Map() {}

void Map::putUnit(Position pos, char unit_type) {
    pos.normalize();
    if (isValid(pos)) {
        std::cout << "Poner unidad en posicion invalida: " << pos.x << "," << pos.y << std::endl;
        return;
    }
    UnitDTO unit{};
    unit.type = unit_type;
    unit.pos_x = pos.x;
    unit.pos_y = pos.y;
    unitsDTO.push_back(unit);
}
