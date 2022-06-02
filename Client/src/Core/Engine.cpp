//
// Created by riclui on 30/05/22.
//

#include "Engine.h"

bool Engine::IsRunning() {
    return m_Running;
}

void Engine::Events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_MOUSEMOTION:
                std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                m_Running = false;
        }
    }
}

void Engine::Update() {
    for(unsigned int i = 0; i != m_players.size(); i++)
        m_players[i].update(FRAME_RATE);
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

