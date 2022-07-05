//
// Created by riclui on 26/06/22.
//

#include "SiloCL.h"

SiloCL::SiloCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(SILO,position, SDL2pp::Point(33,30), id, player, life) {}

void SiloCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera);
}
