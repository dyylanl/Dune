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
#include "ButtonWidtrap.h"
#include "ButtonRefinery.h"
#include <arpa/inet.h>

#define HARKONNEN 1
#define ATREIDES 2
#define ORDOS 3


//-----------------------------------------------------------------------------

Client::Client(std::string ip1, std::string port1) : socket(ip1,port1), protocol() {
}

void Client::crear_partida(const std::string& nombre_jugador, const std::string&  nombre_partida, int cantidad_jugadores){
  this->enviar_nombre_jugador(nombre_jugador);
  this->enviar_accion("crear");
  this->enviar_nombre_partida(nombre_partida);
  this->enviar_cant_jugadores(cantidad_jugadores);
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

void Client::enviar_nombre_jugador(std::string nombre_jugador){
 protocol.sendName(socket, nombre_jugador); 
}

void Client::enviar_accion(std::string comando){
  std::string crear = "crear";
  std::string unirse = "unirse";
  std::string listar = "listar";

  if(comando == crear){
    uint16_t comando_num = 1;
    protocol.sendResponse(socket, comando_num);
  }
  if(comando == unirse){
    uint16_t comando_num = 2;
    protocol.sendResponse(socket, comando_num);
  }
  if(comando == listar){
    uint16_t comando_num = 3;
    protocol.sendResponse(socket, comando_num);
  }
}

std::vector<std::string> Client::listar_partidas(){
  std::vector<std::string> list = this->protocol.recvGameList(socket);
  return list;
}


void Client::enviar_cant_jugadores(int cantidad){
 uint16_t cant_jugadores = cantidad;
  protocol.sendResponse(socket, cant_jugadores); 
}

void Client::enviar_nombre_partida(std::string nombre_partida){
  protocol.sendName(socket, nombre_partida);
}

void Client::launch() {

    try {
      //DESCOMENTAR ESTO PARA PROBAR SIN QT
/*
       // envio el nombre del jugador
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
        std::vector<std::vector<char>> mapa = protocol.recvMap(socket);
*/
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
        std::vector<ObjectGame> gameObjects;
        EventManager eventManager;
        auto *buttonWidtrap = new ButtonWidtrap(textureManager, SDL2pp::Point(1115, 220), SDL2pp::Point(65, 50));
        auto *buttonRefinery = new ButtonRefinery(textureManager, SDL2pp::Point(1115, 280), SDL2pp::Point(65, 50));
        std::vector<Button*> buttons;
        buttons.push_back(buttonWidtrap);
        buttons.push_back(buttonRefinery);
        //mapa de prueba
        std::vector<std::vector<char>> map(50, std::vector<char> (50, 'A') );

        Engine engine(map, buttons, gameObjects, textureManager, eventManager, queueNb, queueB);

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
