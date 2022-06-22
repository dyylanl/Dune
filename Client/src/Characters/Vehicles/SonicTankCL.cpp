//
// Created by riclui on 21/06/22.
//

#include "SonicTankCL.h"

SonicTankCL::SonicTankCL(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life,
                         bool action) : Vehicle("SonicTank", position,
                                            SDL2pp::Point(32,25), id, player,
                                            selecStatus, posAction,
                                            life, action) {}

SDL2pp::Rect SonicTankCL::getShape() {
    return SDL2pp::Rect(m_position, m_size);
}

void SonicTankCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
