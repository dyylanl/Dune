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
            unsigned int sizeObjects = m_objects.size();
            for (unsigned int i = 0; i < sizeObjects; ++i) {
                m_objects[i]->processEvent(event, m_queueB, m_camera);
            }
            unsigned int sizeMenu = m_menu.size();
            for (unsigned int i = 0; i < sizeMenu; ++i) {
                m_menu[i]->processEvent(event, m_queueB, m_camera);
            }
            //m_camera.update(event);
        }
    }
}

void Engine::Update() {
    try {
        m_objects = m_queueNb.front();
        m_queueNb.pop();

        unsigned int sizeObjects = m_objects.size();
        for (unsigned int i = 0; i < sizeObjects; ++i) {
            m_objects[i]->cameraOffset(m_camera);
        }

    } catch (EmptyQueue & e) {
        //std::cerr << e.what() << std::endl;
    }
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_TextureManager.drawMap(m_Renderer, m_mapa, m_camera);
    m_TextureManager.draw(m_Renderer, MENU, SDL2pp::Point(1089, 0), SDL2pp::Point(191, 720));
    for (int i = 0; i < (int) m_objects.size(); ++i) {
        m_objects[i]->draw(m_Renderer, m_TextureManager);
    }

    for (int i = 0; i < (int) m_menu.size(); ++i) {
        m_menu[i]->draw(m_Renderer, m_TextureManager);
    }
    m_Renderer.Present();
}

Engine::Engine(std::vector<std::vector<char>> &mapa, std::vector<std::unique_ptr<ButtonCL>> &menu,TextureManager &textureManager,
               NBQueue<std::vector<std::unique_ptr<GameObject>>> &queueNb, BQueue<std::unique_ptr<CommandCL>> &queueB)
               : m_mapa (mapa), m_menu(std::move(menu)), m_TextureManager(textureManager),
                 m_queueNb(queueNb), m_queueB(queueB){
    m_Running = true;
}

