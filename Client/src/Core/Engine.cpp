//
// Created by riclui on 30/05/22.
//

#include "Engine.h"

bool Engine::IsRunning() {
    return m_Running;
}

void Engine::Events() {
    m_Running = m_eventManager.listen();
}

void Engine::Update() {
    try {
        std::vector<std::unique_ptr<GameObject>> aux;
        m_objects = m_queueNb.front();
        m_queueNb.pop();
        int size = m_objects.size();
        for (int i = 0; i < size; ++i) {
            m_objects[i]->update(m_eventManager, m_queueB);
        }
        //m_TextureManager.getCamera().update(m_eventManager);
    } catch (EmptyQueue & e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_TextureManager.drawMap(m_Renderer, m_mapa);
    m_TextureManager.draw(m_Renderer, MENU, SDL2pp::Point(1089, 0), SDL2pp::Point(191, 720));
    for (int i = 0; i < (int) m_objects.size(); ++i) {
        m_objects[i]->draw(m_Renderer, m_TextureManager);
    }
    m_Renderer.Present();
    //m_objects.clear();
}

Engine::Engine(std::vector<std::vector<char>> &mapa, std::vector<std::unique_ptr<GameObject>> &objects, TextureManager &textureManager, EventManager &eventManager,
               NBQueue<std::vector<std::unique_ptr<GameObject>>> &queueNb, BQueue<std::unique_ptr<CommandCL>> &queueB)
               : m_mapa (mapa), m_objects(std::move(objects)), m_TextureManager(textureManager), m_eventManager(eventManager),
                 m_queueNb(queueNb), m_queueB(queueB){
    m_Running = true;
}

