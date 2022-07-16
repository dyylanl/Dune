//
// Created by riclui on 21/06/22.
//

#include "TrikeCL.h"

TrikeCL::TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                 bool action) : Vehicle(TRIKE, position,
                                    SDL2pp::Point(32,25), id, player,
                                    selecStatus, posAction,
                                    life, action), m_animation(32, 8, m_size, m_position, m_posAction, m_player, m_life, m_selectStatus, m_action){}

void TrikeCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    m_animation.draw(renderer, textureManager, m_textureID, camera);
}