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
#include "../Thread/Unidad.h"
#include "../../../Common/includes/NonBlockingQueue.h"

class Engine {
private:
    std::vector<Player> &m_players;
    TextureManager &m_TextureManager;
    EventManager &m_eventManager;
    bool m_Running;
    NonBlockingQueue<Unidad*> &m_queueNb;
public:
    Engine(std::vector<Player> &players, TextureManager &manager, EventManager &eventManager, NonBlockingQueue<Unidad*> &queue_nb);

    bool IsRunning();

    void Events();

    void Update();

    void Render(SDL2pp::Renderer &m_Renderer);
};


#endif //DUNE_ENGINE_H
