//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_ENGINE_H
#define DUNE_ENGINE_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"
#include "../Characters/Player.h"
#include "../Graphics/TextureManager.h"
#include "../EventManager.h"

class Engine {
private:
    std::vector<Player> &m_players;
    EventManager eventManager;
    bool m_Running;
public:
    Engine();

    bool IsRunning();

    void Events();

    void Update();

    void Render(SDL2pp::Renderer &m_Renderer);

    Engine(std::vector<Player> &players);

    void Quit();
};


#endif //DUNE_ENGINE_H
