//
// Created by riclui on 28/05/22.
//

#include "Animation.h"
#include "../../includes/Client.h"

Animation::Animation(int frameCount, int colCount, SDL2pp::Point size, SDL2pp::Point position, SDL2pp::Point posAction, int player, int life, bool selectStatus, bool action)
: m_frameCount(frameCount), m_colCount(colCount), m_size(size), m_position(position), m_posAction(posAction), m_player(player), m_life(life), m_selectStatus(selectStatus), m_action(action) {}

void Animation::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, char textureID, Camera &camera) {
    if(m_selectStatus) {
        textureManager.drawFrame(renderer, LIFE, m_position - SDL2pp::Point(0,10), SDL2pp::Point(40,8), SDL2pp::Point(0,0), camera);
    }

    SDL2pp::Point posFrame;
    posFrame = selectFrame();
    textureManager.drawFrame(renderer, textureID, m_position, m_size, posFrame, camera);
}

SDL2pp::Point Animation::selectFrame() {
    SDL2pp::Point diff = m_posAction - m_position;
    if (diff.GetX() == 0 && diff.GetY() == 0) {
        return SDL2pp::Point(0,0);
    }
    double theta = 0;
    if(diff.GetX() >= 0) {
        theta = atan2(diff.GetX(), -diff.GetY()) * 180/M_PI;
    } else {
        theta = atan2(diff.GetX(), -diff.GetY()) * 180/M_PI + 360;
    }
    double delta_theta = 360.0 / m_frameCount;
    double aux = theta/delta_theta;
    int row = (int)trunc(aux / m_colCount);
    int col = (int)trunc((aux / m_colCount - row) * 10);
    //std::cout << col << "," << row << std::endl;
    SDL2pp::Point pos(col * m_size.GetX(),row * m_size.GetY());
    return pos;
}


