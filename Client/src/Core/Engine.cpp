//
// Created by riclui on 30/05/22.
//

#include "Engine.h"

bool Engine::IsRunning() {
    return m_Running;
}

void Engine::Events() {
    m_Running = m_eventManager.listen();
    if (m_eventManager.mouseButtonDown(LEFT)) {
        m_queueB.push(new Action(5, 0, m_eventManager.getMouse()));
    }
    if (m_eventManager.mouseButtonDown(RIGHT)) {
        m_queueB.push(new Action(6,0,m_eventManager.getMouse()));
    }
}

void Engine::Update() {
    std::vector<GameObject*> aux;
    aux = m_queueNb.pop();
    if(!aux.empty()) m_objects = aux;

    int size = m_objects.size();
    for (int i = 0; i < size; ++i) {
        m_objects[i]->update(m_eventManager, m_queueB);
    }
    //m_TextureManager.getCamera().update(m_eventManager);
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_TextureManager.drawMap(m_Renderer, m_mapa);
    m_TextureManager.draw(m_Renderer, "menu", SDL2pp::Point(1089, 0), SDL2pp::Point(191, 720));
    for (int i = 0; i < (int) m_objects.size(); ++i) {
        m_objects[i]->draw(m_Renderer, m_TextureManager);
    }
    m_Renderer.Present();
    //m_objects.clear();
    //m_players.clear();
}

Engine::Engine(std::vector<std::vector<char>> &mapa, std::vector<GameObject*> &objects, TextureManager &textureManager, EventManager &eventManager,
               NonBlockingQueue<std::vector<GameObject*>> &queueNb, BlockingQueue<Action*> &queueB)
               : m_mapa (mapa), m_objects(objects), m_TextureManager(textureManager), m_eventManager(eventManager),
                 m_queueNb(queueNb), m_queueB(queueB){
    m_Running = true;
}

