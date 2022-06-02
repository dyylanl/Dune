#include <utility>
#include "../../includes/Model/Map.h"

Map::Map(int rows1, int cols1) : rows(rows1), cols(cols1){
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

Map::~Map() = default;
