#include "../../../includes/Model/Buildings/Refinery.h"
#include "../../../config/GameConfiguration.h"

Refinery::Refinery(const int x, const int y,
                   int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().spiceRefineryEnergy,
                 GameConfiguration::getConfig().spiceRefineryCost,
                 GameConfiguration::getConfig().spiceRefineryHitPoints,
                 GameConfiguration::getConfig().spiceRefineryWidth,
                 GameConfiguration::getConfig().spiceRefineryHeight,
                 REFINERY),
        capacity(GameConfiguration::getConfig().spiceRefinerySpiceCapacity) {}

Refinery::~Refinery() {}

bool Refinery::load(Player &player) {
    this->news = true;
    return news;
}

int Refinery::getCapacity() {
    return this->capacity;
}
