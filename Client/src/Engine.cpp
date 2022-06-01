//
// Created by riclui on 30/05/22.
//

#include "Engine.h"

Engine::Engine() : m_Window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            800, 600, SDL_WINDOW_RESIZABLE),
                   m_Renderer(m_Window, -1, SDL_RENDERER_ACCELERATED),
                   m_texture(m_Renderer,
                             SDL2pp::Surface(DATA_PATH "assets/soldier2.png").SetColorKey(true, 0)),
                   m_TextureManager(m_Renderer),
                   m_Player("soldier", m_texture){
    m_Running = true;
    m_TextureManager.load("soldier", DATA_PATH "assets/soldier2.png");
}

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

void Engine::Render() {
    m_Renderer.Clear();
    m_Player.draw(m_Renderer);
    m_Renderer.Present();
}