#include "../../../includes/Model/Terrains/Rock.h"

Rocks::Rocks() :
        Terrain(ROCK_KEY),
        building(nullptr) {}

void Rocks::buildOn(Building* newBuilding) {
    this->occupied = true;
    this->builtOn = true;
    this->building = newBuilding;
}

Building* Rocks::getBuilding() {
    return this->building;
}

void Rocks::free() {
    this->building = nullptr;
    Terrain::free();
}
