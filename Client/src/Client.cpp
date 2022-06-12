#include "../includes/Client.h"

#include <utility>
#include "../../Common/includes/Socket/Socket.h"
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include "SDL2pp/Renderer.hh"
#include "Graphics/TextureManager.h"
#include "Characters/Player.h"
#include "Core/Engine.h"
#include "Thread/RecvThread.h"
#include <arpa/inet.h>


//-----------------------------------------------------------------------------

Client::Client(std::string ip1, std::string port1) : socket(ip1,port1), protocol() {
    std::cout << "constructor cliente" << std::endl;
}

void Client::launch() {
    try {

        // Se recibe el mapa desde el servidor.
        std::cout << "recibiendo mapa..." << std::endl;
        std::vector<std::vector<char>> mapa;
        mapa = protocol.recvMap(socket);
        int rows = mapa.size();
        int cols = mapa[0].size();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                char key = mapa[i][j];
                if (key == 'P') {
                    const std::string red("\033[0;31m");
                    std::string reset("\033[0m");
                    std::cout << red << key << reset;
                } else if (key == 'C') {
                    const std::string green("\033[0;32m");
                    std::string reset("\033[0m");
                    std::cout << green << key << reset;
                } else {
                    std::cout << key;
                }
            }
            printf("\n");
        }
        printf("\n");


        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("DUNE - v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1280, 720, SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        Camera camera;
        TextureManager textureManager(renderer, camera);
        textureManager.load("carryall", DATA_PATH "assets/carryall.png");
        textureManager.load("missileTank", DATA_PATH "assets/missileTank.png");
        textureManager.load("menu", DATA_PATH "assets/menu.png");
        std::vector<Player> gameObjects;
        EventManager eventManager;



        Engine engine(gameObjects, textureManager, eventManager);
        std::vector<std::vector<int>> posiciones;


        while (engine.IsRunning()) {
            engine.Events();
            engine.Update();
            engine.Render(renderer);
            usleep(FRAME_RATE);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

Client::~Client() = default;

//-----------------------------------------------------------------------------
