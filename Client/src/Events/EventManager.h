//
// Created by riclui on 02/06/22.
//

#ifndef DUNE_EVENTMANAGER_H
#define DUNE_EVENTMANAGER_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"

class EventManager {
private:
    int x;
    int y;
    bool m_MouseButtonLeftState;

public:
    EventManager();

    bool listen();

    void mouseMotion(SDL_Event event);

    void mouseDown(SDL_Event event);

    void mouseUp(SDL_Event event);
};


#endif //DUNE_EVENTMANAGER_H
