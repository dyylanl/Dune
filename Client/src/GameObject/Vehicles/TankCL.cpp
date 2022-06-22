//
// Created by riclui on 21/06/22.
//

#include "TankCL.h"

TankCL::TankCL(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life,
               bool action) : Vehicle("Tank", position,
                                  SDL2pp::Point(32,25), id, player,
                                  selecStatus, posAction,
                                  life, action) {}

SDL2pp::Rect TankCL::getShape() {
    return SDL2pp::Rect(m_position, m_size);
}

void TankCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
