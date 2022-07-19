#include "../../../includes/Model/Units/HeavyInfantry.h"
#include "../../../includes/Model/Terrains/Sand.h"
#include "../../../includes/Model/Terrains/Dunes.h"
#include "../../../includes/Model/Terrains/Rock.h"
#include "../../../includes/Model/Terrains/Summit.h"
#include "../../../includes/Model/Weapons/RocketLauncher.h"
#include "../../../config/GameConfiguration.h"
HeavyInfantry::HeavyInfantry(int x, int y, int player_id1) : Unit(DESVIATOR_KEY, x, y,
                                                                  GameConfiguration::getConfig().heavyInfantryHitPoints,
                                                                  GameConfiguration::getConfig().heavyInfantrySpeed,
                                                                  GameConfiguration::getConfig().heavyInfantryCost, player_id1){}

HeavyInfantry::~HeavyInfantry() {}

bool HeavyInfantry::canMoveAboveTerrain(Terrain &terrain) {
    return terrain == Sand() || terrain == Dunes() || terrain == Rocks() || terrain == Summit();
}

void HeavyInfantry::shoot(Attackable& defender){
    this->rocket = new Rocket(pos,defender.getClosestPosition(pos));
}

bool HeavyInfantry::shotARocket(){
    return (this->rocket!=nullptr);
}

Rocket* HeavyInfantry::viewRocket(){
    return this->rocket;
}

Rocket* HeavyInfantry::getRocket(){
    Rocket* aux = this->rocket;
    this->rocket = nullptr;
    return aux;
}


void HeavyInfantry::reciveBonusDammage(const Weapon &weapon) {
    life -= weapon.getInfantryBonus();
}

void HeavyInfantry::attack(Attackable* enemy) {
    enemy->reciveAttack(RocketLauncher());
}