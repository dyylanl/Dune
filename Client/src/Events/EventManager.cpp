//
// Created by riclui on 02/06/22.
//

#include "EventManager.h"

EventManager::EventManager() {
    m_MouseButtonStates = {false, false};
}

bool EventManager::listen() {
    m_MouseLastPosition = m_MouseCurrPosition;
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
    m_MouseCurrPosition.SetX(event.motion.x);
    m_MouseCurrPosition.SetY(event.motion.y);
}

void EventManager::mouseDown(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonStates[LEFT] = true;

    if(event.button.button == SDL_BUTTON_RIGHT)
        m_MouseButtonStates[RIGHT] = true;
    for (int i = 0; i < (int) m_MouseButtonStates.size(); ++i) {
        std::cout << m_MouseButtonStates[i] << std::endl;
    }
}

void EventManager::mouseUp(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonStates[LEFT] = false;;

    if(event.button.button == SDL_BUTTON_RIGHT)
        m_MouseButtonStates[RIGHT] = false;
    for (int i = 0; i < (int) m_MouseButtonStates.size(); ++i) {
        std::cout << m_MouseButtonStates[i] << std::endl;
    }
}

SDL2pp::Point EventManager::getMouse() {
    return m_MouseCurrPosition;
}
