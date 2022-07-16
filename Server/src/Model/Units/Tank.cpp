#include "../../../includes/Model/Units/Tank.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"
#include "../../../includes/Model/Weapons/Cannon.h"


Tank::Tank(int x, int y,int player_id1) :
        Unit(TANK_KEY,x, y,
             GameConfiguration::getConfig().tankHitPoints,
             GameConfiguration::getConfig().tankSpeed,
             GameConfiguration::getConfig().tankCost, player_id1)
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

void Tank::attack(Attackable* enemy) {
    enemy->reciveAttack(Cannon());
}