#include "../../includes/Model/Map.h"
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../includes/defs.h"

Map::Map(std::string map_path) : load_map(map_path), rows(load_map.getRows()), cols(load_map.getCols()) {
    // EL TERRENO INICIAL SE SETEA CON 'ARENAS'
    std::vector <std::vector<Terrain>> terrain_init
            ((uint16_t) rows, std::vector<Terrain>((uint16_t) cols, Terrain(Position(),'A')));

    std::vector <std::vector<char>> map_init
            ((uint16_t) rows, std::vector<char>((uint16_t) cols, 'A'));

    this->terrrains = terrain_init;
    this->mapa = map_init;

    std::cout << "Se jugara con un mapa de " << load_map.getRows() << " x " << load_map.getCols() << std::endl;

    this->mapa = load_map.getMap();
}

bool Map::canMove(const Unit& unit, Position position) {
    return (isValid(position) && Unit::canMove());
}

// este metodo devuelve falso si la posicion tiene un precipicio
bool Map::isValid(Position position) {
    int x = position.getX();
    int y = position.getY();
    if ( x < 0 || y < 0 || x >= rows || y >= cols) {
        return false;
    }
    if (this->terrrains[x][y].getType() == PRECIPICE_KEY) {
        return false;
    }
    return true;
}

////////////////// IMPLEMENTACION CON TERRENOS //////////////////

void Map::putTerrain(Terrain terrain) {
    if (isValid(terrain.getPosition())) {
        this->terrrains[terrain.getPosition().getX()][terrain.getPosition().getY()] = terrain;
        this->mapa[terrain.getPosition().getX()][terrain.getPosition().getY()] = terrain.getType();
    }
}

void Map::showTerrain() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            char key = this->terrrains[i][j].getType();
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
    return this->terrrains[posX][posY].getType();
}

Unit *Map::selectUnit(int pos_x, int pos_y) {
    Unit* unit = new Unit(1,'T',pos_x,pos_y);
    if (this->mapa[pos_x][pos_y] == 'U') {
        return unit;
    }
    return nullptr;
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
Map::~Map() = default;