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
#include "GameObject/Button/ButtonBuild/ButtonWidtrapCL.h"
#include "GameObject/Button/ButtonBuild/ButtonRefineryCL.h"
#include "Animation/Animation.h"
#include <arpa/inet.h>

#define HARKONNEN 1
#define ATREIDES 2
#define ORDOS 3

#define CREATE_GAME 1
#define JOIN_GAME 2
#define LIST_GAMES 3

//-----------------------------------------------------------------------------

Client::Client() {}

Client::Client(std::string ip1, std::string port1) : socket(ip1,port1), protocol() {
}

void Client::crear_partida(std::string nombre_jugador, std::string  nombre_partida){
  this->enviar_nombre_jugador(nombre_jugador);
  this->enviar_accion("crear");
  this->enviar_nombre_partida(nombre_partida);
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

void Client::enviar_nombre_y_comando(const std::string& nombre_jugador,std::string comando){
  this->protocol.sendName(socket, nombre_jugador);
  this->enviar_accion(comando);
}
/*
std::vector<std::string> Client::listar_partidas(){
  std::vector<std::string> list = this->protocol.recvGameList(socket);
  return list;
}*/

std::vector<std::vector<std::string>> Client::listar_mapas(){
  std::vector<std::vector<std::string>> maps_ = protocol.recvMapsCreated(socket);
  return maps_;
}

void Client::enviar_cant_jugadores(int cantidad){
    uint16_t cant_jugadores = cantidad;
    protocol.sendResponse(socket, cant_jugadores);
}


void Client::enviar_map_id(int map_id){
    protocol.sendResponse(socket, map_id);
}


void Client::enviar_nombre_partida(std::string nombre_partida){
    protocol.sendName(socket, nombre_partida);
}

int Client::recibir_respuesta(){
  return (int) this->protocol.recvResponse(socket);
}

bool Client::partida_iniciada(){
  if(protocol.recvEstablishConnection(socket)) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE INICIE LA PARTIDA
    return true;
  }
  return false;
}

void Client::initSDL(Socket &aSocket, Protocol &aProtocol,
                     std::vector<std::vector<char>> &map) const {

    NBQueue<std::vector<std::unique_ptr<GameObject>>> queueNb;
    BQueue<std::unique_ptr<CommandCL>> queueB;
    RecvThread recvThread(queueNb, aSocket, aProtocol);
    SendThread sendThread(queueB, aSocket, aProtocol);
    recvThread.start();
    sendThread.start();

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("DUNE - v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          1280, 720, SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    Camera camera;
    TextureManager textureManager(renderer, camera);

    loadTextures(textureManager, renderer);
    EventManager eventManager;
    std::vector<std::unique_ptr<GameObject>> objects;

    Engine engine(map, objects, textureManager, eventManager, queueNb, queueB);

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
}

void Client::createGame(Protocol protocol, Socket &socket) {


  // SEND NOMBRE PARTIDA
  std::cout << "\nNombre de la partida: ";
  std::string nombre_partida;
  std::cin >> nombre_partida;
  protocol.sendName(socket, nombre_partida);

  // RECV MAPAS CREADOS
  std::vector<std::vector<std::string>> maps_ = protocol.recvMapsCreated(socket);
  std::cout << "\n\n";
  if (maps_.size() == 0) {
    std::cout << "No hay mapas cargados en el server" << std::endl;
  } else {
  int total_maps_uploaded = (int)maps_.size();
    for (int i = 0; i < total_maps_uploaded; i++) {
    std::cout << "\nMapa " << i+1 << "\nFilas: " << maps_[i][0] << "\nColumnas: " << maps_[i][1] << "\nJugadores Requeridos: " << maps_[i][2] << std::endl;
    }
  }

  // SEND MAP ID
  uint16_t map_id;
  std::cout << "\nSeleccione un mapa: ";
  std::cin >> map_id;
  protocol.sendResponse(socket, map_id);

  
  std::vector<std::vector<char>> map;

  if(protocol.recvEstablishConnection(socket)) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE CREE LA PARTIDA
      std::cout << "Union exitosa" << std::endl;
      if(protocol.recvInitGame(socket)) {
        std::cout << "Se completo la partida..." << std::endl;
        map = protocol.recvMap(socket);
        std::cout << "Mapa recibido..." << std::endl;
        initSDL(socket, protocol, map);
      }  
  } else {
    std::cout << "ERROR UNIENDOME A LA PARTIDA "<< std::endl;
  }

}

void Client::joinGame(Protocol protocol, Socket &socket) {

  std::vector<std::vector<char>> map;
  std::cout << "\nNombre de la partida: ";
  std::string name_game;
  std::cin >> name_game;
  protocol.sendName(socket,name_game);

    // RECV INIT PARTIDA
    if(protocol.recvEstablishConnection(socket)) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE INICIE LA PARTIDA
      std::cout << "Union exitosa" << std::endl;
      if(protocol.recvInitGame(socket)) {
        std::cout << "Se completo la partida..." << std::endl;
        map = protocol.recvMap(socket);
        std::cout << "Mapa recibido..." << std::endl;
        initSDL(socket,protocol,map);
      }  
  } else {
    std::cout << "ERROR UNIENDOME A LA PARTIDA "<< std::endl;
  }
}

void Client::listGames(Protocol protocol, Socket &socket) {
  std::cout << "Partidas creadas: " << std::endl;
  std::vector<std::vector<std::string>> list = protocol.recvGameList(socket);
  if (!list.empty()) {
    int n = (int)list.size();
    for (int i = 0; i < n; i++) {
      std::cout << list[i][2] << " " << list[i][0] << "/" << list[i][1] << std::endl;
    }
  } else {
    std::cout << "No hay partidas creadas..." << std::endl;
  }
}


void Client::launch() {
    std::cout << "Iniciando cliente.... \n\n";
    try {
        std::string ip;
        std::string port;
        std::cout << "IP: ";
        std::cin >> ip;
        std::cout << "\nPORT: ";
        std::cin >> port;
        Socket socket(ip,port);
        Protocol protocol;
        std::cout << "Conexion exitosa.\n";
        std::string nombre;
        std::cout << "\nNombre: ";
        std::cin >> nombre;
        protocol.sendName(socket, nombre);
        std::cout << std::endl;
        std::cout << "  * [1] Crear Partida\n  * [2] Unirse a partida\n  * [3] Listar partidas\n";
        uint16_t comando;
        std::cout << "Ingrese un comando: ";
        std::cin >> comando;
        std::vector<std::vector<char>> map;
        protocol.sendResponse(socket, comando);
        if (comando == CREATE_GAME) {
            createGame(protocol, socket);
            //map = joinGame(protocol, socket);
        } else if (comando == JOIN_GAME) {
            joinGame(protocol, socket);
        } else if (comando == LIST_GAMES) {
            listGames(protocol,socket);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    /*Socket socket_("localhost","8082");
    Protocol protocol_;
    std::vector<std::vector<char>> map(50, std::vector<char> (50, 'A') );
    initSDL(socket_, protocol_, map);*/
}



void Client::loadTextures(TextureManager &textureManager, SDL2pp::Renderer &renderer) const {
    textureManager.load(TRIKE, DATA_PATH "assets/Vehicles/Trike.png");
    textureManager.load(SONIC_TANK, DATA_PATH "assets/Vehicles/SonicTank.png");
    textureManager.load(RAIDER, DATA_PATH "assets/Vehicles/Trike.png");
    textureManager.load(DESVIATOR, DATA_PATH "assets/Vehicles/Deviator.png");
    textureManager.load(TANK, DATA_PATH "assets/Vehicles/Tank.png");
    textureManager.load(DEVASTATOR, DATA_PATH "assets/Vehicles/Devastator.png");
    textureManager.load(HARVESTER, DATA_PATH "assets/Vehicles/Harvester.png");
    textureManager.load(LIGHT_INFANTRY, DATA_PATH "assets/Vehicles/Deviator.png");
    textureManager.load(HEAVY_INFANTRY, DATA_PATH "assets/Vehicles/Tank.png");
    textureManager.load(FREMEN, DATA_PATH "assets/Vehicles/Devastator.png");
    textureManager.load(SARDAUKAR, DATA_PATH "assets/Vehicles/Harvester.png");

    textureManager.load(CONSTRUCTION_YARD, DATA_PATH "assets/Builds/ConstructionYard.png");
    textureManager.load(LIGHT_FACTORY, DATA_PATH "assets/Builds/LightFactory.png");
    textureManager.load(HEAVY_FACTORY, DATA_PATH "assets/Builds/HeavyFactory.png");
    textureManager.load(WIND_TRAP, DATA_PATH "assets/Builds/WindTrap.png");
    textureManager.load(REFINERY, DATA_PATH "assets/Builds/Refinery.png");
    textureManager.load(SILO, DATA_PATH "assets/Builds/Silo.png");
    textureManager.load(BARRACK, DATA_PATH "assets/Builds/Barrack.png");
    textureManager.load(PALACE, DATA_PATH "assets/Builds/Palace.png");

    textureManager.load(BTRIKE, DATA_PATH "assets/Button/Trike.gif");
    textureManager.load(BSONIC_TANK, DATA_PATH "assets/Button/SonicTank.gif");
    textureManager.load(BRAIDER, DATA_PATH "assets/Button/Trike.gif");
    textureManager.load(BDESVIATOR, DATA_PATH "assets/Button/Deviator.gif");
    textureManager.load(BTANK, DATA_PATH "assets/Button/Tank.gif");
    textureManager.load(BDEVASTATOR, DATA_PATH "assets/Button/Devastator.gif");
    textureManager.load(HARVESTER, DATA_PATH "assets/Button/Harvester.gif");
    textureManager.load(BLIGHT_INFANTRY, DATA_PATH "assets/Button/LightInfantry.gif");
    textureManager.load(BHEAVY_INFANTRY, DATA_PATH "assets/Button/HeavyInfantry.gif");
    textureManager.load(BFREMEN, DATA_PATH "assets/Button/Fremen.gif");
    textureManager.load(BSARDAUKAR, DATA_PATH "assets/Button/Sardaukar.gif");

    textureManager.load(BCONSTRUCTION_YARD, DATA_PATH "assets/Button/ConstructionYard.gif");
    textureManager.load(BLIGHT_FACTORY, DATA_PATH "assets/Button/LightFactory.gif");
    textureManager.load(BHEAVY_FACTORY, DATA_PATH "assets/Button/HeavyFactory.gif");
    textureManager.load(BWIND_TRAP, DATA_PATH "assets/Button/WindTrap.gif");
    textureManager.load(BREFINERY, DATA_PATH "assets/Button/Refinery.gif");
    textureManager.load(BSILO, DATA_PATH "assets/Button/Silo.gif");
    textureManager.load(BBARRACK, DATA_PATH "assets/Button/Barrack.gif");
    textureManager.load(BPALACE, DATA_PATH "assets/Button/Palace.gif");

    textureManager.load(MENU, DATA_PATH "assets/menu.png");
    textureManager.load(ARENA, DATA_PATH "assets/Terrain/tile_arena.png");
    textureManager.load(CIMA, DATA_PATH "assets/Terrain/tile_cimas.png");
    textureManager.load(DUNA, DATA_PATH "assets/Terrain/tile_dunas.png");
    textureManager.load(PRECIPICIO, DATA_PATH "assets/Terrain/tile_precipicio.png");
    textureManager.load(ROCA, DATA_PATH "assets/Terrain/tile_roca.png");

}

Client::~Client() = default;

//-----------------------------------------------------------------------------
