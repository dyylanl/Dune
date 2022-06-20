#include "MapReader.h"

MapReader::MapReader(std::string filename) :
    YAMLReader(filename) {}

unsigned MapReader::getRows() const{
    return this->config["Tablero"]["Filas"].as<int>();
}

unsigned MapReader::getCols() const{
    return this->config["Tablero"]["Columnas"].as<int>();
}

std::vector<std::vector<char>> MapReader::getMap() {
    int rows = getRows();
    int cols = getCols();
    std::vector <std::vector<char>> map((int) rows, std::vector<char>((int) cols, 'A'));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::stringstream key_i_j;
            key_i_j << i << "," << j;
            std::string tipo = config["Tablero"][key_i_j.str()]["Tipo"].as<std::string>();
            if (tipo == "Arena") {
                map[i][j] = 'A';
            }
            if (tipo == "Roca") {
                map[i][j] = 'R';

            }
            if (tipo == "Duna") {
                map[i][j] = 'D';

            }
            if (tipo == "Precipicio") {
                map[i][j] = 'P';

            }
            if (tipo == "Cimas") {
                map[i][j] = 'C';

            }
        }
    }
    return map;
}

MapReader::~MapReader() = default;