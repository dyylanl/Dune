//
// Created by riclui on 26/06/22.
//

#include "RefineryCL.h"

RefineryCL::RefineryCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(REFINERY,position, SDL2pp::Point(106,74), id, player, life) {}

void RefineryCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame1(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position+ SDL2pp::Point(-6,20), m_size, posFrame1);
    SDL2pp::Point posFrame2(106,0);
    textureManager.drawFrame(renderer, m_textureID, m_position , m_size, posFrame2);
}
