#include "../../../includes/Model/Units/Trike.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"

Trike::Trike(int x, int y) :
        Unit(x, y,
                      GameConfiguration::getConfig().trikeHitPoints,
                      GameConfiguration::getConfig().trikeSpeed,
                      GameConfiguration::getConfig().trikeCost)
{
}

Trike::~Trike() {}

bool Trike::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rocks();
}

void Trike::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getVehicleBonus();
}
