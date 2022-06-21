#include "../../../includes/Model/Weapons/SmallCannon.h"

SmallCannon::SmallCannon() :
        Weapon(GameConfiguration::getConfig().smallCannonDamage,
               GameConfiguration::getConfig().smallCannonShootingRate,
               GameConfiguration::getConfig().smallCannonBonus) {}

SmallCannon::~SmallCannon() {}

int SmallCannon::getInfantryBonus() const {
    return 0;
}

int SmallCannon::getVehicleBonus() const {
    return bonus;
}

int SmallCannon::getBuildingBonus() const {
    return bonus;
}
