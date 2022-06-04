#include "../../../includes/Model/Terrains/Terrain.h"

char Terrain::getType() {
    return type;
}

bool Terrain::operator==(const Terrain &terrain) {
    return terrain.type == type;
}

void Terrain::occupy(){
    occupied = true;
}

bool Terrain::isOccupied() const{
    return occupied;
}


int Terrain::getSpeedFactor() const {
    return this->speed_factor;
}

Terrain::Terrain(Position pos1, char type1) :
        position(pos1),
        type(type1),
        occupied(false),
        speed_factor(1) {}

Position Terrain::getPosition() {
    return this->position;
}

void Terrain::setType(char type1) {
    this->type = type1;
}


Terrain &Terrain::operator=(const Terrain &otro) {
    this->type = otro.type;
    this->occupied = otro.occupied;
    this->position = otro.position;
    this->speed_factor = otro.speed_factor;
    return *this;
}