#include "../includes/Client.h"

#include <utility>
#include "../../Common/includes/Socket/Socket.h"
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include "SDL2pp/Renderer.hh"
#include "Graphics/TextureManager.h"
#include "Core/Engine.h"
#include "Thread/RecvThread.h"
#include "../../Common/includes/BlockingQueue.h"
#include "../../Common/includes/NonBlockingQueue.h"
#include "Thread/SendThread.h"
#include "GameObject/Button/ButtonWidtrap.h"
#include "GameObject/Button/ButtonRefinery.h"
#include "Animation/Animation.h"
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

        std::string nombre;
        std::cout << "Nombre: ";
        std::cin >> nombre;
        protocol.sendName(socket, nombre);
        std::cout << std::endl;
        std::cout << "Comando de partida (1: crear, 2: unirse, 3: listar):";
        uint16_t comando;
        std::cin >> comando;
        protocol.sendResponse(socket, comando);

        if (comando == 1) {

            std::cout << "\nNombre de la partida: ";
            std::string nombre_partida;
            std::cin >> nombre_partida;
            protocol.sendName(socket, nombre_partida);

            std::cout << "\nMapa de la partida (1: mapa1, 2: mapa2, 3: mapa3): " << std::endl;
            uint16_t map_id;
            std::cin >> map_id;
            protocol.sendResponse(socket, map_id);
            uint16_t response = protocol.recvResponse(socket);
            if (response == 0) {
                std::cout << "se creo la partida" << std::endl;
                std::vector<std::vector<char>> map = protocol.recvMap(socket);

            }
        } else if (comando == 2) {
            std::cout << "\nNombre de la partida: ";
            std::string name_game;
            std::cin >> name_game;
            protocol.sendName(socket,name_game);
            int resp = protocol.recvResponse(socket);
            if (resp == 0) {
                std::cout << "me uni a la partida correctamente" << std::endl;
            }
        } else if (comando == 3) {
            std::cout << "Partidas creadas: " << std::endl;
            std::vector<std::string> list = this->protocol.recvGameList(socket);
            if (!list.empty()) {
                int n = (int)list.size();
                for (int i = 0; i <= (n-2); i = i+3) {
                    std::cout << (list[i+2]);
                    std::cout << " " << list[i] << "/" << list[i+1] << std::endl;
                }
                protocol.recvResponse(socket);
            } else {
                std::cout << "No hay partidas creadas..." << std::endl;
            }
        }

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

}

void Client::loadTextures(TextureManager &textureManager) const {
    textureManager.load("Trike", DATA_PATH "assets/Vehicles/Trike.png");
    textureManager.load("SonicTank", DATA_PATH "assets/Vehicles/SonicTank.png");
    textureManager.load("Deviator", DATA_PATH "assets/Vehicles/Deviator.png");
    textureManager.load("Tank", DATA_PATH "assets/Vehicles/Tank.png");
    textureManager.load("Devastator", DATA_PATH "assets/Vehicles/Devastator.png");
    textureManager.load("Harvester", DATA_PATH "assets/Vehicles/Harvester.png");

    textureManager.load("ConstructionYard", DATA_PATH "assets/Builds/ConstructionYard.png");
    textureManager.load("LightFactory", DATA_PATH "assets/Builds/LightFactory.png");
    textureManager.load("HeavyFactory", DATA_PATH "assets/Builds/HeavyFactory.png");
    textureManager.load("WindTrap", DATA_PATH "assets/Builds/WindTrap.png");
    textureManager.load("Refinery", DATA_PATH "assets/Builds/Refinery.png");
    textureManager.load("Silo", DATA_PATH "assets/Builds/Silo.png");
    textureManager.load("Barrack", DATA_PATH "assets/Builds/Barrack.png");
    textureManager.load("Palace", DATA_PATH "assets/Builds/Palace.png");

    textureManager.load("ButtonConstructionYard", DATA_PATH "assets/Button/ConstructionYard.gif");
    textureManager.load("ButtonLightFactory", DATA_PATH "assets/Button/LightFactory.png");
    textureManager.load("ButtonHeavyFactory", DATA_PATH "assets/Button/HeavyFactory.png");
    textureManager.load("ButtonWindTrap", DATA_PATH "assets/Button/WindTrap.png");
    textureManager.load("ButtonRefinery", DATA_PATH "assets/Button/Refinery.png");
    textureManager.load("ButtonSilo", DATA_PATH "assets/Button/Silo.png");
    textureManager.load("ButtonBarrack", DATA_PATH "assets/Button/Barrack.png");
    textureManager.load("ButtonPalace", DATA_PATH "assets/Button/Palace.png");

    textureManager.load("menu", DATA_PATH "assets/menu.png");
    textureManager.load("arena", DATA_PATH "assets/Terrain/tile_arena.png");
    textureManager.load("cima", DATA_PATH "assets/Terrain/tile_cimas.png");
    textureManager.load("duna", DATA_PATH "assets/Terrain/tile_dunas.png");
    textureManager.load("precipicio", DATA_PATH "assets/Terrain/tile_precipicio.png");
    textureManager.load("roca", DATA_PATH "assets/Terrain/tile_roca.png");

}

Client::~Client() = default;

//-----------------------------------------------------------------------------
