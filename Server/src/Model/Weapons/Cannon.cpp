#include "../../../includes/Model/Weapons/Cannon.h"

Cannon::Cannon() :
        Weapon(GameConfiguration::getConfig().cannonDamage,
               GameConfiguration::getConfig().cannonShootingRate,
               GameConfiguration::getConfig().cannonBonus) {}

Cannon::~Cannon() {}

int Cannon::getInfantryBonus() const {
    return 0;
}

int Cannon::getVehicleBonus() const {
    return 0;
}

int Cannon::getBuildingBonus() const {
    return 0;
}
