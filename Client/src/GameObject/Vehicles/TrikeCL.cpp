//
// Created by riclui on 21/06/22.
//

#include "TrikeCL.h"

TrikeCL::TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                 bool action) : Vehicle(TRIKE, position,
                                    SDL2pp::Point(32,25), id, player,
                                    selecStatus, posAction,
                                    life, action) {}

void TrikeCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame;
    posFrame = this -> posFrame();
    if(m_selectStatus) {
        textureManager.drawFrame(renderer, LIFE, m_position - SDL2pp::Point(0,10), SDL2pp::Point(40,8), SDL2pp::Point(0,0), camera);
    }
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera);
}

SDL2pp::Point TrikeCL::posFrame() {
    //SDL2pp::Point diff = m_posAction-m_position;
    //float theta = atan2(diff.GetX(), -diff.GetY());
    //float delta_theta = 2 * M_PI/frames_size;
    return SDL2pp::Point(0,0);
}
