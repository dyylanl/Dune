#include "../../includes/Model/Map.h"
#include "../../../Common/includes/Exceptions/Exception.h"

Map::Map(int rows1, int cols1) : rows(rows1), cols(cols1){
    std::vector <std::vector<std::string>> map_init
            ((uint16_t) rows, std::vector<std::string>((uint16_t) cols, "A"));
    this->mapa = map_init;
}

bool Map::canMove(const Unit& unit, Position position) {
    return (validPosition(position) && Unit::canMove());
}

void Map::put(Position position, std::string value) {
    if (validPosition(position)) {
        this->mapa[position.getX()][position.getY()] = std::move(value);
    }
}


void Map::showMap() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->mapa[i][j] == "P") {
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


bool Map::validPosition(Position position) {
    int x = position.getX();
    int y = position.getY();
    if ( x < 0 || y < 0 || x >= rows || y >= cols) {
        return false;
    }
    if (this->mapa[x][y] == "P") {
        return false;
    }
    return true;
}

bool Map::isValid(Position position) {
    return validPosition(position);
}


Map::~Map() = default;