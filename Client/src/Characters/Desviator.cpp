//
// Created by riclui on 21/06/22.
//

#include "Desviator.h"

Desviator::Desviator(SDL2pp::Point position, int id, int player,
                     bool selecStatus, SDL2pp::Point posAction, int life, bool action) : Vehicle("Desviator", position,
                                                                                                 SDL2pp::Point(30,30), id, player,
                                                                                                 selecStatus, posAction,
                                                                                                 life, action) {

}

void Desviator::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}

SDL2pp::Rect Desviator::getShape() {
    return SDL2pp::Rect(m_position, m_size);
}
