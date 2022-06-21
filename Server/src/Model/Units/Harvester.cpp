#include "../../../includes/Model/Units/Harvester.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"

Harvester::Harvester(int x, int y) :
        Unit(x, y,
             GameConfiguration::getConfig().harvesterHitPoints,
             GameConfiguration::getConfig().harvesterSpeed,
             GameConfiguration::getConfig().harvesterCost),
        spiceCapacity(GameConfiguration::getConfig().harvesterSpiceCapacity),
        spiceCollected(0),
        farm_speed(GameConfiguration::getConfig().harvesterFarmSpeed),
        actual_farm_speed(0),
        load_speed(GameConfiguration::getConfig().harvesterLoadSpeed),
        actual_load_speed(0) {
}

Harvester::~Harvester() {}

bool Harvester::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rock();
}

void Harvester::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getVehicleBonus();
}


bool Harvester::farm(Map &map) {
    int farm = map.at(farming_position).farm();
    if (farm != 0) {
        spiceCollected += farm;
        return true;
    } else {
        return false;
    }
}

bool Harvester::isFull() {
    return spiceCollected >= spiceCapacity;
}
