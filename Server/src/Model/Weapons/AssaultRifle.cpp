#include "../../../includes/Model/Weapons/AssaultRifle.h"

AssaultRifle::AssaultRifle() :
        Weapon(GameConfiguration::getConfig().assaultRifleDamage,
               GameConfiguration::getConfig().assaultRifleShootingRate,
               GameConfiguration::getConfig().assaultRifleBonus) {}

AssaultRifle::~AssaultRifle() {}

int AssaultRifle::getInfantryBonus() const {
    return bonus;
}

int AssaultRifle::getVehicleBonus() const {
    return 0;
}

int AssaultRifle::getBuildingBonus() const {
    return 0;
}

