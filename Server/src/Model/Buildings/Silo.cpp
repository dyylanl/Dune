#include "../../../includes/Model/Buildings/Silo.h"
#include "../../../config/GameConfiguration.h"

Silo::Silo(const int x, const int y,
           int blockWidth, int blockHeight) :
        Building(SILO_KEY,x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().spiceSiloEnergy,
                 GameConfiguration::getConfig().spiceSiloCost,
                 GameConfiguration::getConfig().spiceSiloHitPoints,
                 GameConfiguration::getConfig().spiceSiloWidth,
                 GameConfiguration::getConfig().spiceSiloHeight,
                 SILO),
        capacity(GameConfiguration::getConfig().spiceSiloSpiceCapacity) {}

Silo::~Silo() {}

int Silo::getCapacity() {
    return this->capacity;
}
