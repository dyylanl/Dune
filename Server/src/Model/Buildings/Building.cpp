#include "../../../includes/Model/Buildings/Building.h"
#include "../../../../Common/includes/Exceptions/Exception.h"

int Building::counter = 0;

Building::Building(const int x, const int y, int blockWidth, int blockHeight,
                   const int energy, const int cost, const int hitPoints,
                   const int width, const int height, BuildingType type):
        Attackable(hitPoints, x, y),
        id(counter),
        width(width),
        height(height),
        energy(energy),
        cost(cost),
        key(type),
        all_positions() {
    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            all_positions.emplace_back(x + j * blockWidth, y + i * blockHeight);
        }
    }
    counter += 1;
}

Building::~Building() {}

void Building::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getBuildingBonus();
}

bool Building::is(Building::BuildingType type) {
    return this->key == type;
}

void Building::demolish() {
    this->life = 0;
}

Position& Building::getClosestPosition(Position& position) {
    int distance = position.sqrtDistance(all_positions[0]);
    Position& closest = all_positions[0];
    for (unsigned i = 0; i < all_positions.size(); i++) {
        if (position.sqrtDistance(all_positions[i]) < distance) {
            closest = all_positions[i];
            distance = position.sqrtDistance(closest);
        }
    }
    return closest;
}

int Building::getCapacity() {
    return 0;
}

bool Building::operator==(const Building &other) {
    return this->id == other.id;
}

/*
Building::BuildingType Building::getBuildType(char build_type) {
    switch (build_type) {
        case 'B': return Building::BARRACKS;
        case 'Y': return Building::CONSTRUCTION_YARD;
        case 'H': return Building::HEAVY_FACTORY;
        case 'L': return Building::LIGHT_FACTORY;
        case 'R': return Building::SPICE_REFINERY;
        case 'S': return Building::SPICE_SILO;
        case 'W': return Building::WIND_TRAP;
        default: throw Exception("Tipo de edificio invalido.\n");
    }
}
*/