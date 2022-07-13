#include "../../../includes/Model/Terrains/Rock.h"
#include <iostream>
Rocks::Rocks() :
        Terrain(ROCK_KEY),
        building(nullptr) {}

void Rocks::buildOn(Building* newBuilding) {
    this->occupied = true;
    this->builtOn = true;
    this->building = newBuilding;
    std::cout << "Construyendo en roca" << std::endl;
}

Building* Rocks::getBuilding() {
    return this->building;
}

void Rocks::free() {
    this->building = nullptr;
    Terrain::free();
}
