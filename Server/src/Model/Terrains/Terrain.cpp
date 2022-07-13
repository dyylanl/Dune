#include <iostream>
#include "../../../includes/Model/Terrains/Terrain.h"

Terrain::Terrain(char key) : key(key), occupied(false), builtOn(false), speed_factor(1) {}

char Terrain::getKey() {
    return key;
}

bool Terrain::operator==(const Terrain &terrain) {
    return terrain.key == key;
}

void Terrain::occupy(){
    occupied = true;
}

Building* Terrain::getBuilding(){
    return nullptr;
}

void Terrain::free(){
    occupied = false;
    builtOn = false;
}

bool Terrain::isOccupied(){
    return occupied || builtOn;
}

bool Terrain::isBuiltOn(){
    return builtOn;
}

int Terrain::getSpice(){
    return 0;
}

int Terrain::farm() {
    return 0;
}

bool Terrain::hasFarm() {
    return false;
}

int Terrain::getSpeedFactor() {
    return this->speed_factor;
}

void Terrain::buildOn(Building* building1) {
    this->occupied = true;
    this->builtOn = true;
    this->building = building1;
}
