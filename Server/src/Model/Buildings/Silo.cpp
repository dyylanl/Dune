#include "../../../includes/Model/Buildings/Silo.h"
#include "../../../config/GameConfiguration.h"

Silo::Silo(const int x, const int y,
           int blockWidth, int blockHeight) :
        Building(SILO_KEY,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().siloEnergy,
                 GameConfiguration::getConfig().siloCost,
                 GameConfiguration::getConfig().siloHitPoints,
                 GameConfiguration::getConfig().siloWidth,
                 GameConfiguration::getConfig().siloHeight,
                 SILO),
        capacity(GameConfiguration::getConfig().siloSpiceCapacity) {}

Silo::~Silo() {}

int Silo::getCapacity() {
    return this->capacity;
}
