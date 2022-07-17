//
// Created by riclui on 26/06/22.
//

#include "WindTrapCL.h"

WindTrapCL::WindTrapCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(WIND_TRAP,position, SDL2pp::Point(63,76), id, player, life) {}

void WindTrapCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera, m_player);
}
