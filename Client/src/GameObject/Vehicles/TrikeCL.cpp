//
// Created by riclui on 21/06/22.
//

#include "TrikeCL.h"

TrikeCL::TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                 bool action) : Vehicle(TRIKE, position,
                                    SDL2pp::Point(32,25), id, player,
                                    selecStatus, posAction,
                                    life, action),  m_framesSize(32), m_cantCol(8){}

void TrikeCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame;
    posFrame = this -> posFrame();
    if(m_selectStatus) {
        textureManager.drawFrame(renderer, LIFE, m_position - SDL2pp::Point(0,10), SDL2pp::Point(40,8), SDL2pp::Point(0,0), camera);
    }
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera);
}

SDL2pp::Point TrikeCL::posFrame() {
    SDL2pp::Point diff = m_posAction - m_position;
    if (diff.GetX() == 0 && diff.GetY() == 0) {
        return SDL2pp::Point(0,0);
    }
    double theta = 0;
    if(diff.GetX() > 0) {
        theta = atan2(diff.GetX(), -diff.GetY()) * 180/M_PI;
    } else {
        theta = atan2(diff.GetX(), -diff.GetY()) * 180/M_PI + 360;
    }
    double delta_theta = 360.0 / m_framesSize;
    double aux = theta/delta_theta;
    int row = (int)trunc(aux/m_cantCol);
    int col = (int)trunc((aux/m_cantCol - row) * 10) - 1;
    SDL2pp::Point pos(col * m_size.GetX(),row * m_size.GetY());
    return pos;
}
