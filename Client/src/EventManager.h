//
// Created by riclui on 02/06/22.
//

#ifndef DUNE_EVENTMANAGER_H
#define DUNE_EVENTMANAGER_H

#include "SDL2pp/SDL2pp.hh"

class EventManager {
private:
    int x;
    int y;
public:
    EventManager();

    bool listen();


};


#endif //DUNE_EVENTMANAGER_H
