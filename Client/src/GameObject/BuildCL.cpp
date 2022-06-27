//
// Created by riclui on 22/06/22.
//

#include "BuildCL.h"

BuildCL::BuildCL(char textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, int life)
: GameObject(textureID, position, size) ,m_id(id), m_player(player), m_life(life) {}
