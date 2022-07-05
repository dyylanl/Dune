#include "../../../includes/Model/Buildings/LightFactory.h"
#include "../../../config/GameConfiguration.h"

LightFactory::LightFactory(const int x, const int y, int blockWidth, int blockHeight) :
        Building(LIGHT_FACTORY_KEY ,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().lightFactoryEnergy,
                 GameConfiguration::getConfig().lightFactoryCost,
                 GameConfiguration::getConfig().lightFactoryHitPoints,
                 GameConfiguration::getConfig().lightFactoryWidth,
                 GameConfiguration::getConfig().lightFactoryHeight,
                 LIGHT_FACTORY)
{}
LightFactory::~LightFactory() {}
