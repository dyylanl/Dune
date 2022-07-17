//
// Created by riclui on 22/06/22.
//

#include "ConstructionYardCL.h"

ConstructionYardCL::ConstructionYardCL(int id, int player, SDL2pp::Point position, int life)
: BuildCL(CONSTRUCTION_YARD,position, SDL2pp::Point(99,89), id, player, life) {}

void ConstructionYardCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera, m_player);
}
