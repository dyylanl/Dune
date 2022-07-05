
#include "../../../includes/Model/Weapons/RocketLauncher.h"
#include "../../../config/GameConfiguration.h"

RocketLauncher::RocketLauncher() :
        Weapon(GameConfiguration::getConfig().rocketLauncherDamage,
               GameConfiguration::getConfig().rocketLauncherShootingRate,
               GameConfiguration::getConfig().rocketLauncherBonus) {}

RocketLauncher::~RocketLauncher() {}

int RocketLauncher::getInfantryBonus() const {
    return 0;
}

int RocketLauncher::getVehicleBonus() const {
    return 0;
}

int RocketLauncher::getBuildingBonus() const {
    return 0;
}

