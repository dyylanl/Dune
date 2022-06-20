#include "../includes/Client.h"

#include <utility>
#include "../../Common/includes/Socket/Socket.h"
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include "SDL2pp/Renderer.hh"
#include "Graphics/TextureManager.h"
#include "Characters/ObjectGame.h"
#include "Core/Engine.h"
#include "Thread/RecvThread.h"
#include "../../Common/includes/BlockingQueue.h"
#include "../../Common/includes/NonBlockingQueue.h"
#include "Thread/SendThread.h"
#include "Button.h"
#include <arpa/inet.h>

#define HARKONNEN 1
#define ATREIDES 2
#define ORDOS 3


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

       /* // envio el nombre del jugador
        std::string nombre = "dylan";
        protocol.sendName(socket, nombre);

        // comando de partida (1: crear, 2: unirse, 3: listar)
        uint16_t comando = 1;
        protocol.sendResponse(socket, comando);

        // nombre de la partida
        std::string nombre_partida = "duelo";
        protocol.sendName(socket, nombre_partida);

        // cantidad de jugadores de la partida
        uint16_t cant_jugadores = 1;
        protocol.sendResponse(socket, cant_jugadores);

        // -------- a partir de este punto el servidor ya creo la partida y lo une al jugador ----------



        // muestro las partidas que hay creadas (para ver que se haya creado bien)
        std::vector<std::string> list = this->protocol.recvGameList(socket);
        if (!list.empty()) {
        int n = (int)list.size();
        for (int i = 0; i <= (n-2); i = i+3) {
            std::cout << (list[i+2]);
            std::cout << " " << list[i] << "/" << list[i+1] << std::endl;
            }
        }
        // como la partida creada es de 1 solo entonces el servidor le envia el mapa
        std::vector<std::vector<char>> mapa = protocol.recvMap(socket);*/

       NonBlockingQueue<Object*> queueNb;
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
        textureManager.load("arena", DATA_PATH "assets/tile_arena.png");
        textureManager.load("cima", DATA_PATH "assets/tile_cimas.png");
        textureManager.load("duna", DATA_PATH "assets/tile_dunas.png");
        textureManager.load("precipicio", DATA_PATH "assets/tile_precipicio.png");
        textureManager.load("roca", DATA_PATH "assets/tile_roca.png");
        textureManager.load("menuWidtrap", DATA_PATH "assets/windtrap.gif");
        std::vector<ObjectGame> gameObjects;
        EventManager eventManager;
        Button button(textureManager, "menuWidtrap", SDL2pp::Point(1115, 220), SDL2pp::Point(65, 50));
        //mapa de prueba
        std::vector<std::vector<char>> map(50, std::vector<char> (50, 'A') );

        Engine engine(map, button, gameObjects, textureManager, eventManager, queueNb, queueB);

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
