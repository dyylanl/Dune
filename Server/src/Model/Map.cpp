#include "../../includes/Model/Map.h"

Map::Map(int rows1, int cols1) : rows(rows1), cols(cols1), matrix(){
    std::vector <std::vector<std::string>> map_init
            ((uint16_t) rows, std::vector<std::string>((uint16_t) cols, "A"));
    this->mapa = map_init;
}

bool Map::isValid(Position position) {
    if (this->mapa[position.getX()][position.getY()] == "A"){
        return true;
    }
    return false;
}

bool Map::canMove(const Unit& unit, Position position) {
    return (isValid(position) && Unit::canMove());
}

void Map::put(Position position, std::string value) {
    this->mapa[position.getX()][position.getY()] = std::move(value);
}


void Map::showMap() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->mapa[i][j] == "B") {
                const std::string red("\033[0;31m");
                std::string reset("\033[0m");
                std::cout << red << this->mapa[i][j] << reset;
            } if (this->mapa[i][j] == "C") {
                const std::string red("\033[0;32m");
                std::string reset("\033[0m");
                std::cout << red << this->mapa[i][j] << reset;
            } else {
                std::cout << this->mapa[i][j];
            }
        }
        printf("\n");
    }
    printf("\n");
}


///////////////////////////// METODOS MATRIX //////////////////////////////////////////////

Terrain& Map::at(Position position) {
    return *matrix.at(position.getY()*cols + position.getX());
}

void Map::showTerrain() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix.at( i*cols + i)->getType();
        }
        printf("\n");
    }
    printf("\n");
}


void Map::put(Building building) {
    this->occupy(building);
}

void Map::occupy(Building building) {
    for (int i = 0; i < building.height; i++) {
        for (int j = 0; j < building.width; j++) {
            this->at(Position(building.getPosition().x, building.getPosition().y)) = Terrain(Position(building.getPosition()),building.key);
        }
    }
}

Terrain Map::at(int x, int y) {
    if ((x < 0) || (y < 0)) {
        throw std::out_of_range("Out of range");
    }
    return *matrix.at((y) * cols + (x));
}


Map::~Map() = default;