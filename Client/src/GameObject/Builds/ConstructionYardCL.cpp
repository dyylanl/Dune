//
// Created by riclui on 22/06/22.
//

#include "ConstructionYardCL.h"

ConstructionYardCL::ConstructionYardCL(SDL2pp::Point position, int id, int player, int life)
: BuildCL("ConstructionYard",position, SDL2pp::Point(99,89), id, player, life) {}

SDL2pp::Rect ConstructionYardCL::getShape() {
    return SDL2pp::Rect(m_position, m_size);
}

void ConstructionYardCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
