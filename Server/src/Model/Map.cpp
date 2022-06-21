#include "../../includes/Model/Map.h"
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../includes/defs.h"

Map::Map(std::string map_path) : map_reader(map_path), rows(map_reader.getRows()), cols(map_reader.getCols()) {
    // EL TERRENO INICIAL SE SETEA CON 'ARENAS'
    std::vector <std::vector<Terrain>> terrain_init
            ((uint16_t) rows, std::vector<Terrain>((uint16_t) cols, Terrain('A')));

    this->terrrains = terrain_init;
    this->mapa = map_reader.getMap();
}

bool Map::canMove(const Unit& unit, Position position) {
    return (isValid(position) && canMove(unit,position));
}

////////////////// IMPLEMENTACION CON TERRENOS //////////////////

void Map::showTerrain() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            char key = this->terrrains[i][j].getKey();
            if (key == PRECIPICE_KEY) {
                const std::string red("\033[0;31m");
                std::string reset("\033[0m");
                std::cout << red << key << reset;
            } else if (key == PLAYER_KEY) {
                const std::string green("\033[0;32m");
                std::string reset("\033[0m");
                std::cout << green << key << reset;
            } else {
                std::cout << key;
            }
        }
        printf("\n");
    }
    printf("\n");
}

char Map::getTypeTerrain(int posX, int posY) {
    return this->terrrains[posX][posY].getKey();
}

Unit* Map::selectUnit(int pos_x, int pos_y) {
    std::cout << "Seleccionando unidad en posicion " << pos_x << "," << pos_y << std::endl;
    Unit* unit = new Unit(5,9,10,2,1);
    return unit;
}

void Map::build(char type, int x, int y) {
    //Building::BuildingType build = Building::getBuildType(type);
    std::cout << "Construyendo un " << "build" << " en la posicion: " << x << "," << y << std::endl;
}


/*
void Map::build(char build_type, int pos_x, int pos_y) {
    Building::BuildingType _build = Building::getBuildingType(build_type);
    int delta_x = _build.heigt;
    int delta_y = _build.width;
    bool flag = true;
    for (int i = pos_x; i < (pos_x+delta_x); ++i) {
        for (int j = pos_y; j < (pos_y+delta_y); ++j) {
            if (this->mapa[i][j] == 'P') {
                flag = false;
            }
        }
    }
    if (flag) {
        for (int i = pos_x; i < (pos_x+delta_x); ++i) {
            for (int j = pos_y; j < (pos_y+delta_y); ++j) {
                this->mapa[i][j] = build_type;
            }
        }
    }
}
*/

Map::~Map() {}

int Map::getWidth() {
    return cols * BLOCK_WIDTH;
}

int Map::getHeight() {
    return rows * BLOCK_HEIGHT;
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
    return reinterpret_cast<Terrain &>(this->terrrains.at((y / BLOCK_HEIGHT) * cols + (x / BLOCK_WIDTH)));
}

Terrain& Map::blockAt(int x, int y) {
    return reinterpret_cast<Terrain &>(this->terrrains.at(y * cols + x));
}

Terrain& Map::at(const Position& pos) {
    return reinterpret_cast<Terrain &>(this->terrrains.at(
            (pos.getY() / BLOCK_HEIGHT) * cols + (pos.getX() / BLOCK_WIDTH)));
}

bool Map::isValid(Position &pos) {
    return pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < cols * BLOCK_HEIGHT && pos.getY() < rows * BLOCK_WIDTH;
}

void Map::put(Unit &unit) {
    units.push_back(&unit);
    this->at(unit.getPosition()).occupy();
}

void Map::put(Building* building) {
    this->occupy(building);
}

void Map::occupy(Building* building) {
    for (int i = 0; i < building->height; i++) {
        for (int j = 0; j < building->width; j++) {
            this->at(building->getPosition().x + j * BLOCK_WIDTH, building->getPosition().y + i * BLOCK_HEIGHT).buildOn(building);
        }
    }
}

bool Map::canMove(Unit& unit, Position pos) {
    return canMove(unit,pos);
}


void Map::free(Building &building) {
    for (int i = 0; i < building.height; i++) {
        for (int j = 0; j < building.width; j++) {
            this->at(building.getPosition().x + j * BLOCK_WIDTH, building.getPosition().y + i * BLOCK_HEIGHT).free();
        }
    }
}

bool Map::canWeBuild(Position& pos, int width, int height, Player& player) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Position aux(pos.getX() + j * BLOCK_WIDTH, pos.getY() + i * BLOCK_HEIGHT);
            if (isValid(aux)) {
                if ((this->at(aux).getKey() != ROCK_KEY) || this->at(aux).isOccupied()) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
    for (int i = -5; i <= height + 5; i++) {
        for (int j = -5; j <= width + 5; j++) {
            Position aux(pos.getX() + j * BLOCK_WIDTH, pos.getY() + i * BLOCK_HEIGHT);
            if (isValid(aux)) {
                if (this->at(aux).isBuiltOn()) {
                    return true;
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
                    if (!(this->at(pos.x + j * BLOCK_WIDTH, pos.y + i * BLOCK_HEIGHT).isOccupied())) {
                        found = true;
                        return Position(pos.x + j * BLOCK_WIDTH, pos.y + i * BLOCK_HEIGHT);
                    }
                }
                catch (std::out_of_range& e) {}
            }
        }
        dist += 1;
    }
    return pos;
}

Position Map::getCornerPosition(Position& pos) {
    return Position((pos.x / BLOCK_WIDTH) * BLOCK_WIDTH, (pos.y / BLOCK_HEIGHT) * BLOCK_HEIGHT);
}

Position Map::getClosestSpeciaPosition(Position pos, int radius) {
    int block_x = (pos.x / BLOCK_HEIGHT);
    int block_y = (pos.y / BLOCK_WIDTH);
    int min_distance = radius + 1;
    Position min_position = pos;
    for (int i = -radius; i <= +radius; ++i) {
        for (int j = -(radius - abs(i)); j <= +(radius - abs(i)); ++j) {
            int cur_pos_x = (block_x + j);
            int cur_pos_y = (block_y + i);
            if ((cur_pos_y + i) >= 0 &&
                (cur_pos_y + i) < cols &&
                (cur_pos_x + j) >= 0 &&
                (cur_pos_x + j) < rows) {
                if ( abs(i) + abs(j) < min_distance
                     && this->blockAt(cur_pos_x, cur_pos_y).hasFarm()) {
                    min_distance = abs(i) + abs(j);
                    min_position = Position(cur_pos_x * BLOCK_HEIGHT, cur_pos_y * BLOCK_WIDTH);
                }
            }
        }
    }

    return min_position;
}

int Map::getSpeedFactorAt(Position &pos) {
    return this->at(pos).getSpeedFactor();
}
