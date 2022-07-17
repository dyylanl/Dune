#include "../../../includes/Model/Buildings/WindTrap.h"
#include "../../../config/GameConfiguration.h"

WindTrap::WindTrap(int player_id,const int x, const int y, int blockWidth, int blockHeight) :
        Building(player_id,WIND_TRAP_KEY,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().windTrapEnergy,
                 GameConfiguration::getConfig().windTrapCost,
                 GameConfiguration::getConfig().windTrapHitPoints,
                 GameConfiguration::getConfig().windTrapWidth,
                 GameConfiguration::getConfig().windTrapHeight,
                 WIND_TRAP)
{}

WindTrap::~WindTrap() {}
