#include "../../../includes/Model/Buildings/Barrack.h"
#include "../../../config/GameConfiguration.h"

Barracks::Barracks(int player_id, const int x, const int y, int blockWidth, int blockHeight) :
        Building(player_id, BARRACKS_KEY, x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().barracksEnergy,
                 GameConfiguration::getConfig().barracksCost,
                 GameConfiguration::getConfig().barracksHitPoints,
                 GameConfiguration::getConfig().barracksWidth,
                 GameConfiguration::getConfig().barracksHeight,
                 BARRACKS) {}

Barracks::~Barracks() {}
