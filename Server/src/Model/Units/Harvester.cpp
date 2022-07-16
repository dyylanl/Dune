#include "../../../includes/Model/Units/Harvester.h"

Harvester::Harvester(int x, int y, int player_id1) :
        Unit(HARVESTER_KEY,
             x,
             y,
             GameConfiguration::getConfig().harvesterHitPoints,
             GameConfiguration::getConfig().harvesterSpeed,
             GameConfiguration::getConfig().harvesterCost,
             player_id1),
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

void Harvester::makeFarming(Map &map) {
    if (actual_farm_speed++ < farm_speed) {
        farming = true;
    } else {
        actual_farm_speed = 0;
    }

    if (!this->isFull()) {
        if (this->farm(map)) {
            farming = true;
        }
        Position new_pos = map.getClosestSpeciaPosition(this->pos, 5);
        if (!(new_pos == this->pos)) {
            farming_position = new_pos;
            map.setDestiny(*this, new_pos.x, new_pos.y);
            farming = false;
        }
    }
    if (this->refinery == nullptr) {
        this->refinery = (Refinery*) player->getClosestBuilding(this->pos, Building::REFINERY);
        if (this->refinery == nullptr) {
            farming = false;
        }
    }
    map.free(*refinery);
    map.setDestiny(*this, refinery->getPosition().x, refinery->getPosition().y);
    map.occupy(refinery);
}

void Harvester::makeLoading(Map &map) {
    if (actual_load_speed++ < load_speed) {
        loading = true;
    } else {
        actual_load_speed = 0;
    }
    if (spiceCollected != 0) {
        if (refinery->load(*player)) {
            spiceCollected -= 1;
            loading = true;
        } else {
            loading = false;
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
    Unit::makeAttack(map);
}

// la cosechadora no tiene arma => supongo q no ataca
void Harvester::attack(Attackable* enemy) {
    return;
}