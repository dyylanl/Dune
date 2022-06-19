#include <iostream>
#include "../../includes/Control/YAMLReader.h"

YAMLReader::YAMLReader(const std::string& filename) :
        config(YAML::LoadFile(filename)) {}

std::string YAMLReader::getPort() const {
    return this->config["port"].as<std::string>();
}

std::string YAMLReader::getMapPath() const {
    return this->config["map_path"].as<std::string>();
}

void YAMLReader::getBuild(const std::string& build_name) {
    std::cout << build_name << std::endl;
    std::cout << "Energy: " << this->config["buildings"][build_name]["energy"].as<int>() << std::endl;
    std::cout << "Capacity: " << this->config["buildings"][build_name]["capacity"].as<int>() << std::endl;
    std::cout << "Cost: " << this->config["buildings"][build_name]["cost"].as<int>() << std::endl;
    std::cout << "Pos x: " << this->config["buildings"][build_name]["x"].as<int>() << std::endl;
    std::cout << "Pos y: " << this->config["buildings"][build_name]["y"].as<int>() << std::endl;
    std::cout << "Hit points: " << this->config["buildings"][build_name]["hit_points"].as<int>() << std::endl;
    std::cout << std::endl;
}

int YAMLReader::getFPS() {
    return this->config["ticks_per_sec"].as<int>();
}

int YAMLReader::getRows() {
    return this->config["Tablero"]["Filas"].as<int>();
}

int YAMLReader::getCols() {
    return this->config["Tablero"]["Columnas"].as<int>();
}

std::vector<std::vector<char>> YAMLReader::getMap() {
    int rows = getRows();
    int cols = getCols();
    std::vector <std::vector<char>> map((int) rows, std::vector<char>((int) cols, 'A'));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::stringstream key_i_j;
            key_i_j << i << "," << j;
            std::string tipo = config["Tablero"][key_i_j.str()]["Tipo"].as<std::string>();
            if (tipo == "Arena") {
                std::cout << "A";
                map[i][j] = 'A';
            }
            if (tipo == "Roca") {
                std::cout << "R";
                map[i][j] = 'R';

            }
            if (tipo == "Duna") {
                std::cout << "D";
                map[i][j] = 'D';

            }
            if (tipo == "Precipicio") {
                std::cout << "P";
                map[i][j] = 'P';

            }
            if (tipo == "Cimas") {
                std::cout << "C";
                map[i][j] = 'C';

            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return map;
}