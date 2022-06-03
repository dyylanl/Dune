//
// Created by riclui on 02/06/22.
//

#include "EventManager.h"

EventManager::EventManager() :x(0), y(0){
}

bool EventManager::listen() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_MOUSEMOTION:
                std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        }
    }
    return true;
}
