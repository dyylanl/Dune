#include "../../includes/Model/Map.h"
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../includes/defs.h"

Map::Map(int rows1, int cols1) : rows(rows1), cols(cols1) {
    // EL TERRENO INICIAL SE SETEA CON 'ARENAS'
    std::vector <std::vector<Terrain>> terrain_init
            ((uint16_t) rows, std::vector<Terrain>((uint16_t) cols, Terrain(Position(),'A')));
    this->terrrains = terrain_init;
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

Map::~Map() = default;