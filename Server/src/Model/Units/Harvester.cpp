#include "../../../includes/Model/Units/Harvester.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"

Harvester::Harvester(int x, int y) :
        Unit(HARVESTER_KEY,x, y,
             GameConfiguration::getConfig().harvesterHitPoints,
             GameConfiguration::getConfig().harvesterSpeed,
             GameConfiguration::getConfig().harvesterCost),
        spiceCapacity(GameConfiguration::getConfig().harvesterSpiceCapacity),
        spiceCollected(0),
        refinery(nullptr),
        farm_speed(GameConfiguration::getConfig().harvesterFarmSpeed),
        actual_farm_speed(0),
        load_speed(GameConfiguration::getConfig().harvesterLoadSpeed),
        actual_load_speed(0) {
}

Harvester::~Harvester() {}

bool Harvester::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rocks();
}

void Harvester::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getVehicleBonus();
}

void Harvester::actionOnPosition(Map &map, Position &pos) {
    map.setDestiny(*this, pos.x, pos.y);
    farming_position = pos;
}

#include <iostream>
void Harvester::makeFarming(Map &map) {
    if (actual_farm_speed++ < farm_speed) {
        std::cout << "Cosechadora farmeando especia." << std::endl;
    } else {
        actual_farm_speed = 0;
    }

    // Revisa si esta llena. Si no lo esta, intenta cosechar
    if (!this->isFull()) {
        // Intenta cosechar, si puede hacerlo, mantiene el estado
        if (this->farm(map)) {
            std::cout << "Cosechadora farmeando especia." << std::endl;
        }

        // Si no puede cosechar, busca un nuevo lugar
        Position new_pos = map.getClosestSpeciaPosition(this->pos, 5);
        if (!(new_pos == this->pos)) {
            farming_position = new_pos;
            map.setDestiny(*this, new_pos.x, new_pos.y);
        }
    }

    // Si esta llena o si no encontro una
    // nueva posicion, busca volver a la refineria
    if (this->refinery == nullptr) {
        this->refinery = (Refinery*)player->getClosestBuilding(this->pos, Building::REFINERY);
        if (this->refinery == nullptr) {
            // Si no encontro ninguna refineria, se queda en el lugar
            return;
        }
    }

    map.free(*refinery);
    map.setDestiny(*this, refinery->getPosition().x, refinery->getPosition().y);
    map.occupy(refinery);

    return;
}

void Harvester::makeLoading(Map &map) {
    if (actual_load_speed++ < load_speed) {
        std::cout << "Cosechadora farmeando especia." << std::endl;
        return;
    } else {
        actual_load_speed = 0;
    }

    if (spiceCollected != 0) {
        if (refinery->load(*player)) {
            spiceCollected -= 1;
            return;
        } else {
            return;
        }
    } else {
        map.setDestiny(*this, farming_position.x, farming_position.y);
    }
}

bool Harvester::farm(Map &map) {
    int farm = map.at(farming_position).farm();
    if (farm != 0) {
        spiceCollected += farm;
        map.updateSpice(farming_position.x, farming_position.y);
        return true;
    } else {
        return false;
    }
}

bool Harvester::isFull() {
    return spiceCollected >= spiceCapacity;
}

void Harvester::makeAttack(Map &map) {
    return;
}
