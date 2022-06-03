//
// Created by riclui on 02/06/22.
//

#include "EventManager.h"

EventManager::EventManager() :x(0), y(0), m_MouseButtonLeftState(false){}

bool EventManager::listen() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_MOUSEMOTION: mouseMotion(event); break;
            case SDL_MOUSEBUTTONDOWN: mouseDown(event); break;
            case SDL_MOUSEBUTTONUP: mouseUp(event); break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        }
    }
    return true;
}

void EventManager::mouseMotion(SDL_Event event) {
    x = event.motion.x;
    y = event.motion.y;
    std::cout << x << "," << y << std::endl;
}

void EventManager::mouseDown(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonLeftState = true;
    std::cout << m_MouseButtonLeftState << std::endl;
}

void EventManager::mouseUp(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonLeftState = false;
    std::cout << m_MouseButtonLeftState << std::endl;
}
