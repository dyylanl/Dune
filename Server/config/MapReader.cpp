#include "MapReader.h"
#include "../includes/Model/Buildings/ConstructionCenter.h"
#include "../includes/types.h"
#include <iostream>
#include <string>

MapReader::MapReader(std::string filename1) :
    YAMLReader(filename1),
    filename(filename1)
 {}

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

std::vector<Building> MapReader::getBuildings() {
    std::cout << "Cargando construcciones de: " << filename << std::endl;
    std::vector<Building> builds;
    int total = this->config["Estructuras"]["Cantidad"].as<unsigned>();
    std::cout << "Cantidad de estructuras: " << total << std::endl;
    for (int i = 0; i < total; ++i) {
        std::string key = std::to_string(i);    
        std::cout << "Key: " << key << std::endl; 
        const int pos_x = this->config["Estructuras"][key]["Pos_x"].as<int>();
        const int pos_y = this->config["Estructuras"][key]["Pos_y"].as<int>();
        std::cout << "Se agrego una construccion en: " << pos_x << "," << pos_y << std::endl;
        ConstructionCenter center(pos_x,pos_y,BLOCK_HEIGHT,BLOCK_WIDTH);
        builds.push_back(center);
    }
    return builds;
}

unsigned MapReader::getReqPlayers() {
    return this->config["Cantidad Jugadores"].as<unsigned>();
}

MapReader::~MapReader() = default;