#include "../../../includes/Model/Buildings/Refinery.h"

Refinery::Refinery(const int x, const int y,
                   int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().spiceRefineryEnergy,
                 GameConfiguration::getConfig().spiceRefineryCost,
                 GameConfiguration::getConfig().spiceRefineryHitPoints,
                 GameConfiguration::getConfig().spiceRefineryWidth,
                 GameConfiguration::getConfig().spiceRefineryHeight,
                 SPICE_REFINERY),
        capacity(GameConfiguration::getConfig().spiceRefinerySpiceCapacity) {}

Refinery::~Refinery() {}

bool Refinery::load(Player &player) {
    this->news = true;
    if (player.gold < player.gold_limit) {
        player.addGold(1);
        return true;
    } else {
        return false;
    }
}

int Refinery::getCapacity() {
    return this->capacity;
}
