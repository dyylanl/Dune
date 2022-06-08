//
// Created by riclui on 30/05/22.
//

#include "Engine.h"

bool Engine::IsRunning() {
    return m_Running;
}

void Engine::Events() {
    m_Running = eventManager.listen();
}

void Engine::Update() {
    for(unsigned int i = 0; i != m_players.size(); i++) {
        if (eventManager.mouseButtonDown(LEFT)) {
            SDL_Rect shape = m_players[i].getShape();
            SDL_Point point = eventManager.getMouse();
            if (SDL_PointInRect(&point, &shape)) {
                std::cout << "objecto seleccionado" << std::endl;
                m_players[i].select();
            }
        }
        m_players[i].update(eventManager,FRAME_RATE);
    }
    m_TextureManager.getCamera().update(eventManager);
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_TextureManager.draw(m_Renderer, "bg", SDL2pp::Point(0, 0), SDL2pp::Point(2100, 1050), SDL_FLIP_NONE);
    for(unsigned int i = 0; i != m_players.size(); i++) {
        m_players[i].draw(m_Renderer);
    }
    m_Renderer.Present();
}

Engine::Engine(std::vector<Player> &players, TextureManager &textureManager) : m_players(players), m_TextureManager(textureManager){
    m_Running = true;
}

