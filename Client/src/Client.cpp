#include "../includes/Client.h"

#include <utility>
#include "../../Common/includes/Socket/Socket.h"
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include "SDL2pp/Renderer.hh"
#include "Graphics/TextureManager.h"
#include "Characters/Player.h"
#include "Core/Engine.h"


//-----------------------------------------------------------------------------

Client::Client(std::string ip1, std::string port1) : ip(std::move(ip1)), port(std::move(port1)) {}

void Client::launch() {
    Socket socket(ip, port);
    const char *data_send = "cliente";
    socket.send(data_send,10);
    try {
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600, SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        Camera camera;
        TextureManager textureManager(renderer, camera);
        textureManager.load("carryall", DATA_PATH "assets/carryall.png");
        textureManager.load("missileTank", DATA_PATH "assets/missileTank.png");
        textureManager.load("bg", DATA_PATH "assets/bg.png");
        Player player1("carryall", textureManager, SDL2pp::Point(300, 300), SDL2pp::Point(64, 61));
        Player player2("missileTank", textureManager, SDL2pp::Point(0, 0), SDL2pp::Point(34, 34));
        std::vector<Player> gameObjects;
        gameObjects.push_back(player1);
        gameObjects.push_back(player2);
        Engine engine(gameObjects, textureManager);
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

    try {
        socket.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "Warning: error while shutting-down socket.");
    }
}

Client::~Client() = default;

//-----------------------------------------------------------------------------
