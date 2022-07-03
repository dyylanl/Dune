//
// Created by riclui on 26/06/22.
//

#include "BarrackCL.h"

BarrackCL::BarrackCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(BARRACK,position, SDL2pp::Point(73,73), id, player, life) {}

void BarrackCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
