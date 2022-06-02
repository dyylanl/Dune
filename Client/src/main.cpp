#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>
#include <vector>
#include "Characters/Player.h"
#include "Core/Engine.h"

int main(int argc, char** argv){
    try {
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600, SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        TextureManager textureManager(renderer);
        textureManager.load("carryall", DATA_PATH "assets/carryall.png");
        textureManager.load("missileTank", DATA_PATH "assets/missileTank.png");
        Player player1("carryall", textureManager, 300, 300);
        Player player2("missileTank", textureManager, 0, 0);
        std::vector<Player> gameObjects;
        gameObjects.push_back(player1);
        gameObjects.push_back(player2);
        Engine engine(gameObjects);
        while (engine.IsRunning()) {
            engine.Events();
            engine.Update();
            engine.Render(renderer);
            usleep(FRAME_RATE);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}