//
// Created by riclui on 02/06/22.
//

#ifndef DUNE_EVENTMANAGER_H
#define DUNE_EVENTMANAGER_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"

enum MouseButton{LEFT, RIGHT};

class EventManager {
private:
    SDL2pp::Point m_MouseCurrPosition;
    SDL2pp::Point m_MouseLastPosition;
    std::vector<bool> m_MouseButtonStates;

    void mouseMotion(SDL_Event event);

    void mouseDown(SDL_Event event);

    void mouseUp(SDL_Event event);

public:
    EventManager();

    bool listen();

    SDL2pp::Point getMouse();

    bool mouseButtonDown(MouseButton button);
};


#endif //DUNE_EVENTMANAGER_H
