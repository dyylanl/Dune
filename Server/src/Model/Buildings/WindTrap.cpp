#include "../../../includes/Model/Buildings/WindTrap.h"
#include "../../../config/GameConfiguration.h"

WindTrap::WindTrap(const int x, const int y, int blockWidth, int blockHeight) :
        Building(WIND_TRAP_KEY,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().windTrapEnergy,
                 GameConfiguration::getConfig().windTrapCost,
                 GameConfiguration::getConfig().windTrapHitPoints,
                 GameConfiguration::getConfig().windTrapWidth,
                 GameConfiguration::getConfig().windTrapHeight,
                 WIND_TRAP)
{}

WindTrap::~WindTrap() {}