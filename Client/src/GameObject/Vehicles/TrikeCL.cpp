//
// Created by riclui on 21/06/22.
//

#include "TrikeCL.h"

TrikeCL::TrikeCL(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life,
                 bool action) : Vehicle("Trike", position,
                                    SDL2pp::Point(32,25), id, player,
                                    selecStatus, posAction,
                                    life, action) {}

void TrikeCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
