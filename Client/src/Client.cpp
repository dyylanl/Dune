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

void Client::crear_partida( const std::string&  house,const std::string& name, const std::string&  req){
    int cantidad = stoi(req);
    uint16_t casa = (uint16_t) obtener_numero_casa(house);
    this->protocol.createGame(this->socket,casa,name,cantidad);
}

int Client::obtener_numero_casa(const std::string& casa) {
  std::string Harkonnen = "Harkonnen";
  std::string Atreides = "Atreides";
  std::string Ordos = "Ordos";
  if (casa == Harkonnen) {
    return 0;
  }
  if (casa == Atreides) {
    return 1;
  }
  if (casa == Ordos) {
    return 2;
  }
  return -1;
}


void Client::launch() {
    try {
        /*NonBlockingQueue<Unidad*> queueNb;
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
        protocol.recvCommand(socket);*/


        NonBlockingQueue<Unidad*> queueNb;
        BlockingQueue<Action*> queueB;
        RecvThread recvThread(queueNb, socket, protocol);
        SendThread sendThread(queueB, socket, protocol);
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
        std::vector<Player> gameObjects;
        EventManager eventManager;
        Engine engine(gameObjects, textureManager, eventManager, queueNb, queueB);

        while (engine.IsRunning()) {
            engine.Events();
            engine.Update();
            engine.Render(renderer);
            usleep(FRAME_RATE);
        }

        sendThread.stop();
        recvThread.stop();
        sendThread.join();
        recvThread.join();
         

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

}

Client::~Client() = default;

//-----------------------------------------------------------------------------
