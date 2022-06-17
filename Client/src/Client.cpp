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
#include "../../Common/includes/BlockingQueue.h"
#include "../../Common/includes/NonBlockingQueue.h"
#include "Thread/SendThread.h"
#include <arpa/inet.h>

#define HARKONNEN 1

//-----------------------------------------------------------------------------

Client::Client(std::string ip1, std::string port1) : socket(ip1,port1), protocol() {
}

void Client::launch() {
    try {
        NonBlockingQueue<Unidad*> queueNb;
        BlockingQueue<Action*> queueB;
        RecvThread recvThread(queueNb, socket, protocol);
        SendThread sendThread(queueB, socket, protocol);

        std::string name = "jugador";
        protocol.sendName(socket, name);
        protocol.sendResponse(socket, HARKONNEN);
        std::vector<std::string> list = this->protocol.recvGameList(socket);
        protocol.sendResponse(socket,1); // le manda al server que quiere jugar en el mapa 1
        if (!list.empty()) {
            int n = (int)list.size();
            for (int i = 0; i <= (n-2); i = i+3) {
                std::cout << (list[i+2]);
                std::cout << " " << list[i] << "/" << list[i+1] << std::endl;
            }
        }
        protocol.recvCommand(socket);
        /*
        recvThread.start();
        sendThread.start();



        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("DUNE - v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1280, 720, SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        Camera camera;
        TextureManager textureManager(renderer, camera);

        textureManager.load("carryall", DATA_PATH "assets/carryall.png");
        textureManager.load("Tanque", DATA_PATH "assets/missileTank.png");
        textureManager.load("menu", DATA_PATH "assets/menu.png");
        //Player tank("missileTank",textureManager,SDL2pp::Point(0,0),SDL2pp::Point(30,30));
        std::vector<Player> gameObjects;
        //gameObjects.push_back(tank);
        EventManager eventManager;
        Engine engine(gameObjects, textureManager, eventManager, queueNb, queueB);

        while (engine.IsRunning()) {
            engine.Events();
            engine.Update();
            engine.Render(renderer);
            usleep(FRAME_RATE);
        }
        recvThread.stop();
        recvThread.join();*/
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

}

Client::~Client() = default;

//-----------------------------------------------------------------------------
