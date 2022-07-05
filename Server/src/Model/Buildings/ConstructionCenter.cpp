#include "../../../includes/Model/Buildings/ConstructionCenter.h"
#include "../../../config/GameConfiguration.h"

ConstructionCenter::ConstructionCenter(const int x, const int y, int blockWidth, int blockHeight) :
        Building(CONSTRUCTION_CENTER_KEY ,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().constructionCenterEnergy,
                 GameConfiguration::getConfig().constructionCenterCost,
                 GameConfiguration::getConfig().constructionCenterHitPoints,
                 GameConfiguration::getConfig().constructionCenterWidth,
                 GameConfiguration::getConfig().constructionCenterHeight,
                 CONSTRUCTION_CENTER)
{}

ConstructionCenter::~ConstructionCenter() {}
