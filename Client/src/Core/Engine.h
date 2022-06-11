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
#include "../Camera/Camera.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"

class Engine {
private:
    std::vector<Player> &m_players;
    TextureManager &m_TextureManager;
    EventManager &m_eventManager;
    Socket &socket;
    Protocol protocol;
    bool m_Running;
public:
    Engine(std::vector<Player> &players, TextureManager &manager, EventManager &eventManager , Socket &skt);

    bool IsRunning();

    void Events();

    void Update();

    void Render(SDL2pp::Renderer &m_Renderer);
};


#endif //DUNE_ENGINE_H
