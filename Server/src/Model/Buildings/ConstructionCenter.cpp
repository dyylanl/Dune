#include "../../../includes/Model/Buildings/ConstructionCenter.h"
#include "../../../config/GameConfiguration.h"

ConstructionCenter::ConstructionCenter(int player_id,const int x, const int y, int blockWidth, int blockHeight) :
        Building(player_id,CONSTRUCTION_CENTER_KEY ,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().constructionCenterEnergy,
                 GameConfiguration::getConfig().constructionCenterCost,
                 GameConfiguration::getConfig().constructionCenterHitPoints,
                 GameConfiguration::getConfig().constructionCenterWidth,
                 GameConfiguration::getConfig().constructionCenterHeight,
                 CONSTRUCTION_CENTER)
{}

ConstructionCenter::~ConstructionCenter() {}
