#include "../../../includes/Model/Buildings/ConstructionCenter.h"

ConstructionCenter::ConstructionCenter(const int x, const int y, int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().constructionCenterEnergy,
                 GameConfiguration::getConfig().constructionCenterCost,
                 GameConfiguration::getConfig().constructionCenterHitPoints,
                 GameConfiguration::getConfig().constructionCenterWidth,
                 GameConfiguration::getConfig().constructionCenterHeight,
                 CONSTRUCTION_CENTER)
{}

ConstructionCenter::~ConstructionCenter() {}
