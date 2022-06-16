//
// Created by riclui on 02/06/22.
//

#include "EventManager.h"

EventManager::EventManager() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    if(m_KeyStates == nullptr){
        std::cout << "Error loading keyboard state!\n";
        exit(-1);
    }
    m_MouseButtonStates = {false, false};
    runnig = true;
}

bool EventManager::listen() {
    m_MouseLastPosition = m_MouseCurrPosition;
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
            case SDL_MOUSEMOTION: mouseMotion(event); break;
            case SDL_MOUSEBUTTONDOWN: mouseDown(event); break;
            case SDL_MOUSEBUTTONUP: mouseUp(event); break;
            case SDL_QUIT: return false;
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
}

void EventManager::mouseUp(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        m_MouseButtonStates[LEFT] = false;;

    if(event.button.button == SDL_BUTTON_RIGHT)
        m_MouseButtonStates[RIGHT] = false;
}

SDL2pp::Point EventManager::getMouse() {
    return m_MouseCurrPosition;
}

bool EventManager::mouseButtonDown(MouseButton button) {
    return m_MouseButtonStates[button];
}

void EventManager::KeyDown() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void EventManager::KeyUp() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

bool EventManager::GetKeyDown(SDL_Scancode key){
    if(m_KeyStates[key] == 1)
        return true;
    return false;
}
