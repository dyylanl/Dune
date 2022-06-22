//
// Created by riclui on 22/06/22.
//

#include "Vehicle.h"

void Vehicle::update(EventManager &eventManager, BlockingQueue<Action *> &queue) {
    if (eventManager.mouseButtonDown(LEFT)) {
        SDL_Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL_Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            std::cout << "click button" << std::endl;
        }
    }
}
