#include <iostream>
#include "../../includes/Control/YAMLReader.h"

YAMLReader::YAMLReader(const std::string& filename) :
        config(YAML::LoadFile(filename)) {}

std::string YAMLReader::getPort() const {
    return this->config["port"].as<std::string>();
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