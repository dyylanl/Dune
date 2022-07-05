
#include "../../../includes/Model/Units/LightInfantry.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"
#include "../../../includes/Model/Terrains/Summit.h"
#include "../../../includes/Model/Weapons/Weapons.h"

LightInfantry::LightInfantry(int x, int y) :
        Unit(x, y, GameConfiguration::getConfig().lightInfantryHitPoints,
                      GameConfiguration::getConfig().lightInfantrySpeed,
                      GameConfiguration::getConfig().lightInfantryCost)
{
}

LightInfantry::~LightInfantry() {}

bool LightInfantry::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rocks() || terrain == Summit();
}

void LightInfantry::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getInfantryBonus();
}
