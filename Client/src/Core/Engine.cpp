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
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        m_Player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        m_Player.moveRigth();
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        m_Player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        m_Player.stopMoving();
                        break;
                }
            }// Fin KEY_UP
                break;
            case SDL_MOUSEMOTION:
                std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                m_Running = false;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
}

void Engine::Update() {
    m_Player.update(FRAME_RATE);
}

void Engine::Render(SDL2pp::Renderer &m_Renderer) {
    m_Renderer.Clear();
    m_Player.draw(m_Renderer);
    m_Renderer.Present();
}

Engine::Engine(Player &player) : m_Player(player){
    m_Running = true;
}
