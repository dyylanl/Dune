//
// Created by riclui on 22/06/22.
//

#include "Button.h"

void Button::update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue) {
    if (eventManager.mouseButtonDown(LEFT)) {
        SDL_Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL_Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            std::cout << "click button" << std::endl;
        }
    }
}

void Button::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}
