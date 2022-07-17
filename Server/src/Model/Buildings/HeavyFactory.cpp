#include "../../../includes/Model/Buildings/HeavyFactory.h"
#include "../../../config/GameConfiguration.h"

HeavyFactory::HeavyFactory(int player_id, const int x, const int y, int blockWidth, int blockHeight) :
        Building(player_id, HEAVY_FACTORY_KEY,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().heavyFactoryEnergy,
                 GameConfiguration::getConfig().heavyFactoryCost,
                 GameConfiguration::getConfig().heavyFactoryHitPoints,
                 GameConfiguration::getConfig().heavyFactoryWidth,
                 GameConfiguration::getConfig().heavyFactoryHeight,
                 HEAVY_FACTORY)
{}

HeavyFactory::~HeavyFactory() {}
