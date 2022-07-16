
#include "../../../includes/Model/Units/Raider.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"
#include "../../../includes/Model/Weapons/Cannon.h"

Raider::Raider(int x, int y,int player_id1) :
        Unit(RAIDER_KEY,x, y, GameConfiguration::getConfig().raiderHitPoints,
             GameConfiguration::getConfig().raiderSpeed,
             GameConfiguration::getConfig().raiderCost,player_id1)
{
}

Raider::~Raider() {}

bool Raider::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rocks();
}

void Raider::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getVehicleBonus();
}

void Raider::attack(Attackable* enemy) {
    enemy->reciveAttack(Cannon());
}