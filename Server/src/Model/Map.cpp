#include "../../includes/Model/Map.h"

#include <utility>
#include "../../../Common/includes/Exceptions/Exception.h"

Map::Map(std::string map_path) : map_reader(std::move(map_path)),
rows(map_reader.getRows()),
cols(map_reader.getCols()),
units(),
builds() {
    std::vector <std::vector<Terrain>> terrain_init
            ((uint16_t) rows, std::vector<Terrain>((uint16_t) cols, Terrain('A')));
    this->terrrains = terrain_init;
    this->mapa = map_reader.getMap();
    int rows_ = mapa.size();
    int cols_ = mapa[0].size();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            char type = this->mapa[i][j];
            for (int k = 0; k < BLOCK_HEIGHT; ++k) {
                for (int l = 0; l < BLOCK_WIDTH; ++l) {
                    this->terrrains[k][l] = Terrain(type);
                }
            }
        }
    }

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
    Unit* unit = new Unit(pos_x,pos_y,10,2,1);
    return unit;
}

void Map::build(char type, int x, int y) {
    auto build1 = Building::getBuildType(type, x, y);
    std::cout << "Construyendo un edificio en la posicion: " << x << "," << y << std::endl;
    if (canWeBuild(build1.getPosition(), BLOCK_WIDTH, BLOCK_HEIGHT)) {
        builds.push_back(&build1);

    }
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
    if ((x < 0) || (y < 0) || x > rows || y > cols) {
        throw std::out_of_range("Out of range");
    }
    return reinterpret_cast<Terrain &>(this->terrrains[x][y]);
}

Terrain& Map::at(const Position& pos) {
    return reinterpret_cast<Terrain &>(this->terrrains[pos.getX()][pos.getY()]);
}

bool Map::isValid(Position &pos) {
    return (pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < cols * BLOCK_HEIGHT && pos.getY() < rows * BLOCK_WIDTH);
}

void Map::put(Unit &unit) {
    units.push_back(&unit);
    this->at(unit.getPosition()).occupy();
}

void Map::put(Building* building) {
    builds.push_back(building);
    this->occupy(building);
}

void Map::occupy(Building* building) {
    for (int i = 0; i < building->height+BLOCK_HEIGHT; i++) {
        for (int j = 0; j < building->width+BLOCK_WIDTH; j++) {
            this->at(building->getPosition().x+i, building->getPosition().y+j).buildOn(building);
        }
    }
}

bool Map::canMove(Unit& unit, Position pos) {
    return canMove(unit,pos);
}

void Map::free(Building &building) {
    for (int i = 0; i < building.height+BLOCK_HEIGHT; i++) {
        for (int j = 0; j < building.width+BLOCK_WIDTH; j++) {
            this->at(building.getPosition().x +i, building.getPosition().y + j).free();
        }
    }
}

bool Map::canWeBuild(Position& pos, int width, int height) {
    // busco que la posicion este dentro del mapa y que sea roca para poder buildear
    for (int i = 0; i < height+BLOCK_HEIGHT; i++) {
        for (int j = 0; j < width+BLOCK_WIDTH; j++) {
            Position aux(pos.getX() + i, pos.getY() + j);
            if (isValid(aux)) {
                if ((this->at(aux).getKey() != ROCK_KEY) || this->at(aux).isOccupied()) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
    // me fijo que el terreno sea buildeable
    for (int i = -5; i <= height+BLOCK_HEIGHT + 5; i++) {
        for (int j = -5; j <= width + 5+BLOCK_WIDTH; j++) {
            Position aux(pos.getX() + i, pos.getY() + j);
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
        for (int i = - dist; i <= building->height+dist+BLOCK_HEIGHT; i++) {
            for (int j =  - dist; j <= building->width+dist+BLOCK_WIDTH; j++) {
                try {
                    if (!(this->at(pos.x + i, pos.y + j).isOccupied())) {
                        return {pos.x + i, pos.y + j};
                    }
                }
                catch (std::out_of_range& e) {}
            }
        }
        dist += 1;
        if (dist == 50) {found=true;}
    }
    return pos;
}

int Map::getSpeedFactorAt(Position &pos) {
    return this->at(pos).getSpeedFactor();
}
