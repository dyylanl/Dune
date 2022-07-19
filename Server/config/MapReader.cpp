#include <iostream>
#include "MapReader.h"
#include "../includes/types.h"
#include "../config/GameConfiguration.h"
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
                map[i][j] = SAND_KEY;
            }
            else if (tipo == "Roca") {
                map[i][j] = ROCK_KEY;
            }
            else if (tipo == "Duna") {
                map[i][j] = DUNE_KEY;
            }
            else if (tipo == "Precipicio") {
                map[i][j] = PRECIPICE_KEY;
            }
            else if (tipo == "Cimas") {
                map[i][j] = SUMMIT_KEY;
            }
        }
    }
    return map;
}

std::vector<std::vector<int>> MapReader::getSpice() {
    int rows = getRows();
    int cols = getCols();
    std::vector <std::vector<int>> map_spice((int) rows, std::vector<int>((int) cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::stringstream key_i_j;
            key_i_j << i << "," << j;
            int spice = config["Tablero"][key_i_j.str()]["Cantidad Especia"].as<int>();
            map_spice[i][j] = spice;
        }
    }
    return map_spice;
}

unsigned MapReader::getReqPlayers() {
    return this->config["Cantidad Jugadores"].as<unsigned>();
}

ConstructionCenter* MapReader::getConstructionCenterFor(InstanceId id) {
    int x = this->config["Estructuras"][std::to_string(id)]["Pos_x"].as<int>();
    int y = this->config["Estructuras"][std::to_string(id)]["Pos_y"].as<int>();
    return new ConstructionCenter((int)id,x,y,GameConfiguration::getConfig().constructionCenterWidth,GameConfiguration::getConfig().constructionCenterHeight);
}

int MapReader::getTotalBuildings() {
    return this->config["Estructuras"]["Cantidad"].as<int>();
}

MapReader::~MapReader() = default;