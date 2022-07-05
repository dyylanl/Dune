//
// Created by dypa on 04/07/22.
//
#include "../../../includes/Model/Buildings/Palace.h"
#include "../../../config/GameConfiguration.h"

Palace::Palace(const int x, const int y, int blockWidth, int blockHeight) :
        Building(PALACE_KEY, x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().barracksEnergy,
                 GameConfiguration::getConfig().barracksCost,
                 GameConfiguration::getConfig().barracksHitPoints,
                 GameConfiguration::getConfig().barracksWidth,
                 GameConfiguration::getConfig().barracksHeight,
                 BARRACKS) {}

Palace::~Palace() {}
