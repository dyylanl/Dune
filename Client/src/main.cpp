#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <csignal>
#include "Player.h"
#include "Engine.h"

int main(int argc, char** argv){
    try {
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        Engine engine;
        engine.load("soldier", DATA_PATH "assets/soldier2.png");
        while (engine.IsRunning()) {
            engine.Events();
            engine.Update();
            engine.Render();
            usleep(FRAME_RATE);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}