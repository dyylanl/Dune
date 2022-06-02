#include "../../../includes/Model/Terrains/Terrain.h"

Terrain::Terrain() : key('A'), occupied(false), speed_factor(1) {}

Terrain::Terrain(char key) : key(key), occupied(false), speed_factor(1) {}

char Terrain::getKey() {
    return key;
}

bool Terrain::operator==(const Terrain &terrain) {
    return terrain.key == key;
}

void Terrain::occupy(){
    occupied = true;
}

bool Terrain::isOccupied(){
    return occupied;
}


int Terrain::getSpeedFactor() {
    return this->speed_factor;
}

void Terrain::buildOn(Building building) {
    occupy();
}
