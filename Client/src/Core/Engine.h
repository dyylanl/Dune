//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_ENGINE_H
#define DUNE_ENGINE_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"
#include "../Graphics/TextureManager.h"
#include "../Events/EventManager.h"
#include "../Camera/Camera.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Thread/Action.h"
#include "../Button/ButtonWidtrap.h"

class Engine {
private:
    std::vector<std::vector<char>> m_mapa;
    std::vector<GameObject*> m_objects;
    TextureManager &m_TextureManager;
    EventManager &m_eventManager;
    bool m_Running;
    NonBlockingQueue<std::vector<GameObject*>> &m_queueNb;
    BlockingQueue<Action*> &m_queueB;
public:
    Engine(std::vector<std::vector<char>>& mapa, std::vector<GameObject*> &objects, TextureManager &manager, EventManager &eventManager, NonBlockingQueue<std::vector<GameObject*>> &queue_nb, BlockingQueue<Action*> &queueB);

    bool IsRunning();

    void Events();

    void Update();

    void Render(SDL2pp::Renderer &m_Renderer);
};


#endif //DUNE_ENGINE_H
