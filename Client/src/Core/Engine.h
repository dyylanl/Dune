//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_ENGINE_H
#define DUNE_ENGINE_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"
#include "../Characters/Player.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventManager.h"
#include "Camera.h"
#include "../../../Common/includes/Socket/Socket.h"

class Engine {
private:
    std::vector<Player> &m_players;
    EventManager eventManager;
    TextureManager &m_TextureManager;
    bool m_Running;
public:
    Engine(std::vector<Player> &players, TextureManager &manager);

    bool IsRunning();

    void Events();

    void Update(Socket &skt, int &tam, std::vector<std::vector<int>> &posiciones);

    void Render(SDL2pp::Renderer &m_Renderer);
};


#endif //DUNE_ENGINE_H
