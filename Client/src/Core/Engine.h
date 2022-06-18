//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_ENGINE_H
#define DUNE_ENGINE_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"
#include "../Characters/ObjectGame.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventManager.h"
#include "../Camera/Camera.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include "../Characters/Object.h"
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Thread/Action.h"

class Engine {
private:
    std::vector<ObjectGame> &m_players;
    TextureManager &m_TextureManager;
    EventManager &m_eventManager;
    bool m_Running;
    NonBlockingQueue<Object*> &m_queueNb;
    BlockingQueue<Action*> &m_queueB;
public:
    Engine(std::vector<ObjectGame> &players, TextureManager &manager, EventManager &eventManager, NonBlockingQueue<Object*> &queue_nb, BlockingQueue<Action*> &queueB);

    bool IsRunning();

    void Events();

    void Update();

    void Render(SDL2pp::Renderer &m_Renderer);
};


#endif //DUNE_ENGINE_H
