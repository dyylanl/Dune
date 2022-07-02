//
// Created by riclui on 30/05/22.
//

#include "Engine.h"
#include "../GameObject/Button/ButtonUnit/ButtonRaiderCL.h"

bool Engine::IsRunning() {
    return m_Running;
}

void Engine::Events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) {
            m_Running = false;
        } else{
            unsigned int size1 = m_objects.size();
            for (unsigned int i = 0; i < size1; ++i) {
                m_objects[i]->update(event, m_queueB);
            }
            unsigned int size2 = m_menu.size();
            for (unsigned int i = 0; i < size2; ++i) {
                m_menu[i]->update(event, m_queueB);
            }
        }
    }

}

void Engine::Update() {
    try {
        std::vector<std::unique_ptr<GameObject>> aux;
        m_objects = m_queueNb.front();
        m_queueNb.pop();
    } catch (EmptyQueue & e) {
        //std::cerr << e.what() << std::endl;
    }
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_TextureManager.drawMap(m_Renderer, m_mapa);
    m_TextureManager.draw(m_Renderer, MENU, SDL2pp::Point(1089, 0), SDL2pp::Point(191, 720));
    for (int i = 0; i < (int) m_objects.size(); ++i) {
        m_objects[i]->draw(m_Renderer, m_TextureManager);
    }

    for (int i = 0; i < (int) m_menu.size(); ++i) {
        m_menu[i]->draw(m_Renderer, m_TextureManager);
    }
    m_Renderer.Present();
}

Engine::Engine(std::vector<std::vector<char>> &mapa, std::vector<std::unique_ptr<GameObject>> &objects, std::vector<std::unique_ptr<ButtonCL>> &menu,TextureManager &textureManager, EventManager &eventManager,
               NBQueue<std::vector<std::unique_ptr<GameObject>>> &queueNb, BQueue<std::unique_ptr<CommandCL>> &queueB)
               : m_mapa (mapa), m_objects(std::move(objects)), m_menu(std::move(menu)), m_TextureManager(textureManager), m_eventManager(eventManager),
                 m_queueNb(queueNb), m_queueB(queueB){
    m_Running = true;
}

