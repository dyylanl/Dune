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
        if (eventManager.getMouseButtonLeftState()) {
            SDL_Rect shape = m_players[i].getShape();
            SDL_Point point = eventManager.getMouse();
            if (SDL_PointInRect(&point, &shape)) {
                std::cout << "objecto seleccionado" << std::endl;
                m_players[i].select();
            }
        }
        m_players[i].update(eventManager,FRAME_RATE);
    }
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    for(unsigned int i = 0; i != m_players.size(); i++)
        m_players[i].draw(m_Renderer);
    m_Renderer.Present();
}

Engine::Engine(std::vector<Player> &players) : m_players(players){
    m_Running = true;
}

void Engine::Quit() {
    m_Running = false;
}

