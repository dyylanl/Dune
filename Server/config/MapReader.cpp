#include "MapReader.h"
#include "../includes/types.h"

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
            else if (tipo == "Roca") {
                map[i][j] = 'R';

            }
            else if (tipo == "Duna") {
                map[i][j] = 'D';

            }
            else if (tipo == "Precipicio") {
                map[i][j] = 'P';

            }
            else if (tipo == "Cimas") {
                map[i][j] = 'C';

            }
        }
    }
    return map;
}

std::vector<BuildingDTO> MapReader::getBuildings() {
    std::vector<BuildingDTO> builds;
    int total = this->config["Estructuras"]["Cantidad"].as<unsigned>();
    for (int i = 0; i < total; ++i) {
        const int pos_x = this->config["Estructuras"][std::to_string(i)]["Pos_x"].as<int>();
        const int pos_y = this->config["Estructuras"][std::to_string(i)]["Pos_y"].as<int>();
        BuildingDTO center;
        center.pos_x = pos_x;
        center.pos_y = pos_y; 
        center.height = 3;
        center.width = 3;
        center.life = 500;
        center.type = CONSTRUCTION_CENTER_KEY;
        builds.push_back(center);
    }
    return builds;
}

unsigned MapReader::getReqPlayers() {
    return this->config["Cantidad Jugadores"].as<unsigned>();
}

MapReader::~MapReader() = default;