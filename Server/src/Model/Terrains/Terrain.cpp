#include "../../../includes/Model/Terrains/Terrain.h"

Terrain::Terrain() : key('.'), occupied(false), speed_factor(1) {}

Terrain::Terrain(char key) : key(key), occupied(false), /*builtOn(false), */speed_factor(1) {}

char Terrain::getKey() {
    return key;
}

bool Terrain::operator==(const Terrain &terrain) {
    return terrain.key == key;
}

void Terrain::occupy(){
    occupied = true;
}
/*
void Terrain::buildOn(Building* building){}
*/
Building* Terrain::getBuilding(){
    return nullptr;
}

void Terrain::free(){
    occupied = false;
    //builtOn = false;
}

bool Terrain::isOccupied(){
    return occupied; /*|| builtOn*/
}
/*
bool Terrain::isBuiltOn(){
    return builtOn;
}
*/
int Terrain::getSpice(){
    return 0;
}

int Terrain::farm() {
    return 0;
}

bool Terrain::hasFarm() {
    return false;
}

int Terrain::getSpeedFactor() const {
    return this->speed_factor;
}
