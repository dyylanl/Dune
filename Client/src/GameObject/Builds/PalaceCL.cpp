//
// Created by riclui on 26/06/22.
//

#include "PalaceCL.h"

PalaceCL::PalaceCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(PALACE,position, SDL2pp::Point(99,109), id, player, life) {}

void PalaceCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
