#include "../../../includes/Model/Units/Tank.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"

Tank::Tank(int x, int y) :
        Unit(x, y,
             GameConfiguration::getConfig().tankHitPoints,
             GameConfiguration::getConfig().tankSpeed,
             GameConfiguration::getConfig().tankCost)
{
}

Tank::~Tank()
{
}

bool Tank::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rocks();
}

void Tank::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getVehicleBonus();
}
