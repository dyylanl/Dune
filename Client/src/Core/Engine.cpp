//
// Created by riclui on 30/05/22.
//

#include "Engine.h"

#define X 100
#define Y 100

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
    Object *unit;
    unit = m_queueNb.pop();
    if (unit != nullptr) {
        ObjectGame object(unit, m_TextureManager);
        m_players.push_back(object);
    }
    m_TextureManager.getCamera().update(m_eventManager);
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();

    for (int i = 0; i < (int) m_mapa.size(); ++i) {
        for (int j = 0; j < (int) m_mapa[0].size(); ++j) {
            char key = m_mapa[i][j];
            switch (key) {
                case 'A': m_TextureManager.drawMap(m_Renderer,"arena",SDL2pp::Point(j*X, i*X), SDL2pp::Point(X, X), SDL_FLIP_NONE);
                    break;
                case 'P': m_TextureManager.drawMap(m_Renderer,"precipicio",SDL2pp::Point(j*X, i*X), SDL2pp::Point(X, X), SDL_FLIP_NONE);
                    break;
                case 'R': m_TextureManager.drawMap(m_Renderer,"roca",SDL2pp::Point(j*X, i*X), SDL2pp::Point(X, X), SDL_FLIP_NONE);
                    break;
                case 'D': m_TextureManager.drawMap(m_Renderer,"duna",SDL2pp::Point(j*X, i*X), SDL2pp::Point(X, X), SDL_FLIP_NONE);
                    break;
                case 'C': m_TextureManager.drawMap(m_Renderer,"cima",SDL2pp::Point(j*X, i*X), SDL2pp::Point(X, X), SDL_FLIP_NONE);
                    break;
            }
        }
    }

    m_TextureManager.draw(m_Renderer, "menu", SDL2pp::Point(1089, 0), SDL2pp::Point(191, 720), SDL_FLIP_NONE);
    for(unsigned int i = 0; i != m_players.size(); i++) {
        m_players[i].draw(m_Renderer);
    }
    m_Renderer.Present();
    m_players.clear();
}

Engine::Engine(std::vector<std::vector<char>> &mapa, std::vector<ObjectGame> &players, TextureManager &textureManager, EventManager &eventManager,
               NonBlockingQueue<Object*> &queueNb, BlockingQueue<Action*> &queueB)
               : m_mapa (mapa), m_players(players), m_TextureManager(textureManager), m_eventManager(eventManager),
               m_queueNb(queueNb), m_queueB(queueB){
    m_Running = true;
}

