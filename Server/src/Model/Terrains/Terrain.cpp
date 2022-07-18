#include <iostream>
#include "../../../includes/Model/Terrains/Terrain.h"

Terrain::Terrain(char key) : key(key), occupied(false), builtOn(false), speed_factor(1), spice(0) {}

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
    return this->spice;
}

void Terrain::setSpice(int spice1) {
    this->spice = spice1;
}

int Terrain::farm() {
    if (this->spice != 0) {
        this->spice -= 1;
        return 1;
    } else {
        return 0;
    }
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
