#include "../../../includes/Model/Terrains/Rock.h"


Rock::Rock() :
        Terrain(ROCK_KEY),
        building(nullptr) {}
/*
void Rock::buildOn(Building* newBuilding) {
    this->occupied = true;
    this->builtOn = true;
    this->building = newBuilding;
}
*/
Building* Rock::getBuilding() {
    return this->building;
}

void Rock::free() {
    this->building = nullptr;
    Terrain::free();
}
