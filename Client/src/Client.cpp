#include "../includes/Client.h"

#include <utility>
#include "../../Common/includes/Socket/Socket.h"
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include "SDL2pp/Renderer.hh"
#include "Graphics/TextureManager.h"
#include "Characters/Player.h"
#include "Core/Engine.h"
#include <arpa/inet.h>


//-----------------------------------------------------------------------------

Client::Client(std::string ip1, std::string port1) : socket(ip1,port1), protocol() {}

void Client::launch() {
    try {
        char operation = 0;
        while (1) {
            protocol.operationRecv(socket, operation);
            if(operation == 4) {
                crearUnidad();
            }
        }

        /*std::vector<int> pos = protocol.recvPosition(this->socket);
        std::cout << pos[0] << "," << pos[1] << std::endl;
        std::string input;
        while (input != "q") {
            std::cin >> input;
        }*/
/*
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1280, 720, SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        Camera camera;
        TextureManager textureManager(renderer, camera);
        textureManager.load("carryall", DATA_PATH "assets/carryall.png");
        textureManager.load("missileTank", DATA_PATH "assets/missileTank.png");
        textureManager.load("menu", DATA_PATH "assets/menu.png");
        //Player player1("carryall", textureManager, SDL2pp::Point(300, 300), SDL2pp::Point(64, 61));
        Player player2("missileTank", textureManager, SDL2pp::Point(pos[0] * 30, pos[1] * 30), SDL2pp::Point(34, 34));
        std::vector<Player> gameObjects;
        //gameObjects.push_back(player1);
        gameObjects.push_back(player2);
        Engine engine(gameObjects, textureManager);
        int tam = 0;
        std::vector<std::vector<int>> posiciones;
        while (engine.IsRunning()) {
            engine.Events();
            engine.Update(socket, tam, posiciones);
            engine.Render(renderer);
            usleep(FRAME_RATE);
        }
        */
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
    /*
    try {
        socket.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "Warning: error while shutting-down socket.");
    }
    */
}

void Client::crearUnidad() {
    int unitId = protocol.idUnidRecv(socket);
    char unitType = protocol.typeUnidRecv(socket);
    std::vector<int> pos = protocol.recvPosition(socket);
    if (unitType == 't') {
        std::cout << "crear tank " << unitId << ":" << pos[0] << "," << pos[1] << std::endl;
    }
    if (unitType == 'o') {
        std::cout << "crear otro: " << unitId << ":" << pos[0] << "," << pos[1] << std::endl;
    }
}

Client::~Client() = default;

//-----------------------------------------------------------------------------
