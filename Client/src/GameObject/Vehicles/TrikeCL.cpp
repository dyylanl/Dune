//
// Created by riclui on 21/06/22.
//

#include "TrikeCL.h"

TrikeCL::TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                 bool action) : Vehicle(TRIKE, position,
                                    SDL2pp::Point(32,25), id, player,
                                    selecStatus, posAction,
                                    life, action),  m_framesSize(32), cantCol(8), cantFil(4){}

void TrikeCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame;
    posFrame = this -> posFrame();
    if(m_selectStatus) {
        textureManager.drawFrame(renderer, LIFE, m_position - SDL2pp::Point(0,10), SDL2pp::Point(40,8), SDL2pp::Point(0,0), camera);
    }
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera);
}

SDL2pp::Point TrikeCL::posFrame() {
    /*SDL2pp::Point diff = m_posAction-m_position;
    float theta = 0;
    if(diff.GetX() > 0) {
        theta = atan2(diff.GetY(), diff.GetX()) * 180/M_PI;
    } else {
        theta = atan2(diff.GetY(), diff.GetX()) * 180/M_PI - 180;
    }
    std::cout << diff << std::endl;
    std::cout << theta << std::endl;*/
    /*float theta = atan2(diff.GetX(), -diff.GetY());
    float delta_theta = 2 * M_PI / m_framesSize;
    float aux = (theta / delta_theta) / cantCol;
    int row = trunc(aux);
    int col = trunc(aux * 10) -1;
    //std::cout << "posAct: " << m_posAction << std::endl;
    //std::cout <<  "pos: " << m_position << std::endl;
    //std::cout << diff << std::endl;
    //std::cout << theta << std::endl;
    //std::cout << theta / delta_theta << std::endl;
    std::cout << "row: " << row << std::endl;
    std::cout << "col: " << col << std::endl;*/
    return SDL2pp::Point(0,0);
}
