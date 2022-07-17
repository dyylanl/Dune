//
// Created by dypa on 04/07/22.
//
#include "../../../includes/Model/Buildings/Palace.h"
#include "../../../config/GameConfiguration.h"

Palace::Palace(int player_id,const int x, const int y, int blockWidth, int blockHeight) :
        Building(player_id,PALACE_KEY, x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().palaceEnergy,
                 GameConfiguration::getConfig().palaceCost,
                 GameConfiguration::getConfig().palaceHitPoints,
                 GameConfiguration::getConfig().palaceWidth,
                 GameConfiguration::getConfig().palaceHeight,
                 PALACE) {}

Palace::~Palace() {}
