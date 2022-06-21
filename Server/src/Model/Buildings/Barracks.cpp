#include "../../../includes/Model/Buildings/Barracks.h"

Barracks::Barracks(const int x, const int y, int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().barracksEnergy,
                 GameConfiguration::getConfig().barracksCost,
                 GameConfiguration::getConfig().barracksHitPoints,
                 GameConfiguration::getConfig().barracksWidth,
                 GameConfiguration::getConfig().barracksHeight,
                 BARRACKS) {}

Barracks::~Barracks() {}
