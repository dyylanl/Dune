//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_ENGINE_H
#define DUNE_ENGINE_H

#include <SDL2pp/SDL2pp.hh>
#include "Player.h"

class Engine {
private:
    SDL2pp::Window m_Window;
    SDL2pp::Renderer m_Renderer;
    SDL2pp::Texture m_im;
    Player m_Player;
    bool m_Running;
public:
    Engine();


    bool IsRunning();

    void Events();

    void Update();

    void Render();
};


#endif //DUNE_ENGINE_H
