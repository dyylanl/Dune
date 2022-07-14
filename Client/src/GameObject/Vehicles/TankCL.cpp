//
// Created by riclui on 21/06/22.
//

#include "TankCL.h"

TankCL::TankCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
               bool action) : Vehicle(TANK, position,
                                  SDL2pp::Point(32,25), id, player,
                                  selecStatus, posAction,
                                  life, action) {}

void TankCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame(0,0);
    if(m_selectStatus) {
        textureManager.drawFrame(renderer, LIFE, m_position - SDL2pp::Point(0,10), SDL2pp::Point(40,8), SDL2pp::Point(0,0), camera);
    }
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera);
}
