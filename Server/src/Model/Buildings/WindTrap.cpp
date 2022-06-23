#include "../../../includes/Model/Buildings/WindTrap.h"

WindTrap::WindTrap(const int x, const int y, int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().windTrapEnergy,
                 GameConfiguration::getConfig().windTrapCost,
                 GameConfiguration::getConfig().windTrapHitPoints,
                 GameConfiguration::getConfig().windTrapWidth,
                 GameConfiguration::getConfig().windTrapHeight,
                 WIND_TRAP)
{}

WindTrap::~WindTrap() {}
