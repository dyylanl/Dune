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

#define HARKONNEN 1

//-----------------------------------------------------------------------------

Client::Client(std::string ip1, std::string port1) : socket(ip1,port1), protocol() {
    std::cout << "constructor cliente" << std::endl;
}

void Client::launch() {
    try {
        int send;
        while (send != 0) {
            std::cout << "Enviando: ";
            std::cin >> send;
            protocol.sendResponse(socket, send);
        }


/*
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
        Engine engine(gameObjects, textureManager, eventManager, socket);


        while (engine.IsRunning()) {
            engine.Events();
            engine.Update();
            engine.Render(renderer);
            usleep(FRAME_RATE);
        }*/
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

Client::~Client() = default;

//-----------------------------------------------------------------------------
