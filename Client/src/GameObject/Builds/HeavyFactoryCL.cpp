//
// Created by riclui on 26/06/22.
//

#include "HeavyFactoryCL.h"

HeavyFactoryCL::HeavyFactoryCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(HEAVY_FACTORY,position, SDL2pp::Point(99,89), id, player, life) {}

void HeavyFactoryCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
