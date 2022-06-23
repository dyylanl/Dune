#include "../../../includes/Model/Buildings/Silo.h"

Silo::Silo(const int x, const int y,
           int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
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
