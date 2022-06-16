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
    Unidad *unit;
    unit = m_queueNb.pop();
    if (unit != nullptr) {
        Player tank(unit->getUnitType(),m_TextureManager,unit->getPosition(),SDL2pp::Point(30,30));
        m_players.push_back(tank);
    }
    for(unsigned int i = 0; i != m_players.size(); i++) {
        if (m_eventManager.mouseButtonDown(LEFT)) {
            SDL_Rect shape = m_players[i].getShape();
            SDL_Point point = m_eventManager.getMouse();
            if (SDL_PointInRect(&point, &shape)) {
                std::cout << "objecto seleccionado" << std::endl;
                m_players[i].select();
            }
        }
        m_players[i].update(m_eventManager, FRAME_RATE);
    }
    m_TextureManager.getCamera().update(m_eventManager);
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_TextureManager.draw(m_Renderer, "menu", SDL2pp::Point(1089, 0), SDL2pp::Point(191, 720), SDL_FLIP_NONE);
    for(unsigned int i = 0; i != m_players.size(); i++) {
        m_players[i].draw(m_Renderer);
    }
    m_Renderer.Present();
    m_players.clear();
}

Engine::Engine(std::vector<Player> &players, TextureManager &textureManager, EventManager &eventManager, NonBlockingQueue<Unidad*> &queueNb) : m_players(players), m_TextureManager(textureManager), m_eventManager(eventManager), m_queueNb(queueNb){
    m_Running = true;
}

