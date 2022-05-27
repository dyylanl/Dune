#include "../../includes/Model/Map.h"

Map::Map(int x, int y) {
    if (x <= 0 || y <= 0) {
        throw Exception("Invalid map initialization.\n");
    }
    rows = x;
    columns = y;
    std::vector <std::vector<std::string>> map_init((uint16_t) rows, std::vector<std::string>((uint16_t) columns, "."));
    this->world = map_init;
}

void Map::showMap() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            std::cout << this->world[i][j];
        }
        printf("\n");
    }
    printf("\n");
}

std::string Map::getPos(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        throw Exception("Invalid getPos.\n");
    }
    return this->world[x][y];
}

void Map::setValue(int pColumn, int pRow, char value) {
    if (pRow < 0 || pRow >= rows) {
        throw Exception {"Set value in row invalid."};
    }
    if (pColumn < 0 || pColumn >= columns) {
        throw Exception {"Set value in column invalid."};
    }
    this->world[pRow][pColumn] = value;
}

Map::~Map() {
    std::cout << "Destruyendo mapa..." << std::endl;
}

bool Map::canMove(Unit& unit, Position pos) {
    int posx = pos.getX();
    int posy = pos.getY();
    if (world[posx][posy] != ".") {
        return false;
    }
    return unit.canMove();
}

bool Map::isValid(Position &pos) const {
    return ((pos.getX() >= 0) && (pos.getY() >= 0) && (pos.getX() < columns)
    && (pos.getY() < rows) && (getPos(pos.getX(), pos.getY()) == "."));
}
