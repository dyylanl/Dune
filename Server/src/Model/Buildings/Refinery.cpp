#include "../../../includes/Model/Buildings/Refinery.h"
#include "../../../config/GameConfiguration.h"

Refinery::Refinery(int player_id, const int x, const int y,
                   int blockWidth, int blockHeight) :
        Building(player_id,REFINERY_KEY,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().refineryEnergy,
                 GameConfiguration::getConfig().refineryCost,
                 GameConfiguration::getConfig().refineryHitPoints,
                 GameConfiguration::getConfig().refineryWidth,
                 GameConfiguration::getConfig().refineryHeight,
                 REFINERY),
        capacity(GameConfiguration::getConfig().refinerySpiceCapacity) {}

Refinery::~Refinery() {}

bool Refinery::load(Player &player) {
    return true;
}

int Refinery::getCapacity() {
    return this->capacity;
}
