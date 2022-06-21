#include "../../../includes/Model/Buildings/HeavyFactory.h"

HeavyFactory::HeavyFactory(const int x, const int y, int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().heavyFactoryEnergy,
                 GameConfiguration::getConfig().heavyFactoryCost,
                 GameConfiguration::getConfig().heavyFactoryHitPoints,
                 GameConfiguration::getConfig().heavyFactoryWidth,
                 GameConfiguration::getConfig().heavyFactoryHeight,
                 HEAVY_FACTORY)
{}

HeavyFactory::~HeavyFactory() {}
