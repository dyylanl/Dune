//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrap.h"

void ButtonWidtrap::draw(SDL2pp::Renderer &renderer) {
    m_textureManager.draw(renderer, m_name, m_position, m_size);
}

ButtonWidtrap::ButtonWidtrap(TextureManager &textureManager, SDL2pp::Point position, SDL2pp::Point size)
: m_textureManager(textureManager), m_name("menuWidtrap"), m_position(position), m_size(size){
    m_textureManager.load("menuWidtrap", DATA_PATH "assets/windtrap.gif");
}
