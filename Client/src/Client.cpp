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
#include "GameObject/Button/ButtonUnit/ButtonRaiderCL.h"
#include "GameObject/Button/ButtonUnit/ButtonTrikeCL.h"
#include "GameObject/Button/ButtonBuild/ButtonBarrackCL.h"
#include "GameObject/Button/ButtonBuild/ButtonConstructionYardCL.h"
#include "GameObject/Button/ButtonBuild/ButtonHeavyFactoryCL.h"
#include "GameObject/Button/ButtonBuild/ButtonLightFactoryCL.h"
#include "GameObject/Button/ButtonBuild/ButtonPalaceCL.h"
#include "GameObject/Button/ButtonBuild/ButtonSiloCL.h"
#include "GameObject/Button/ButtonUnit/ButtonHarvesterCL.h"
#include "GameObject/Button/ButtonUnit/ButtonHeavyInfantryCL.h"
#include "GameObject/Button/ButtonUnit/ButtonLightInfantryCL.h"
#include "GameObject/Button/ButtonUnit/ButtonSardaukarCL.h"
#include "GameObject/Button/ButtonUnit/ButtonTankCL.h"
#include "../../Common/includes/RateController.h"
#include "GameObject/Button/ButtonUnit/ButtonSonicTankCL.h"
#include "GameObject/Button/ButtonUnit/ButtonDesviatorCL.h"
#include "GameObject/Button/ButtonUnit/ButtonDevastatorCL.h"
#include "SDL2pp/Mixer.hh"
#include "SDL2pp/Music.hh"
#include "Sounds/SoundManager.h"
#include <arpa/inet.h>

#define HARKONNEN 1
#define ATREIDES 2
#define ORDOS 3

#define CREATE_GAME 1
#define JOIN_GAME 2
#define LIST_GAMES 3

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//-----------------------------------------------------------------------------

Client::Client() {}

Client::Client(std::string ip1, std::string port1) : m_socket(ip1,port1), m_protocol() {
}

void Client::enviar_nombre_jugador(std::string nombre_jugador){
 m_protocol.sendName(m_socket, nombre_jugador);
}

void Client::enviar_accion(std::string comando){
  std::string crear = "crear";
  std::string unirse = "unirse";
  std::string listar = "listar";

  if(comando == crear){
    uint16_t comando_num = 1;
    m_protocol.sendResponse(m_socket, comando_num);
  }
  if(comando == unirse){
    uint16_t comando_num = 2;
    m_protocol.sendResponse(m_socket, comando_num);
  }
  if(comando == listar){
    uint16_t comando_num = 3;
    m_protocol.sendResponse(m_socket, comando_num);
  }
}

std::vector<std::vector<std::string>> Client::listar_partidas(){
  std::vector<std::vector<std::string>> list = this->m_protocol.recvGameList(m_socket);
  return list;
}

std::vector<std::vector<std::string>> Client::listar_mapas(){
  std::vector<std::vector<std::string>> maps_ = m_protocol.recvMapsCreated(m_socket);
  return maps_;
}

void Client::enviar_map_id(int map_id){
    m_protocol.sendResponse(m_socket, map_id);
}


void Client::enviar_nombre_partida(std::string nombre_partida){
    m_protocol.sendName(m_socket, nombre_partida);
}

bool Client::conexion_exitosa(){
  if(this->m_protocol.recvEstablishConnection(m_socket)) {
      uint16_t posX = 0;
      uint16_t posY = 0;
      posX = m_protocol.recvPosition(m_socket);
      posY = m_protocol.recvPosition(m_socket);
      m_initialPos.SetX(-posX*15);
      m_initialPos.SetY(-posY*15);
     // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE INICIE LA PARTIDA
    return true;
  }
  return false;
}


bool Client::partida_iniciada(){
  if(this->m_protocol.recvInitGame(m_socket)) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE INICIE LA PARTIDA
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

    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL2pp::SDLMixer mix(MIX_INIT_OGG);
    SDL2pp::Window window("DUNE - v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    TextureManager textureManager(renderer);

    loadTextures(textureManager, renderer);
    std::vector<std::unique_ptr<ButtonCL>> menu;
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonBarrackCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonHeavyFactoryCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonLightFactoryCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonPalaceCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonRefineryCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonSiloCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonWidtrapCL(1, 1, 10, false, false)));

    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonHarvesterCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonSonicTankCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonDesviatorCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonRaiderCL(1, 1, 10, false, false)));
    //menu.push_back(std::unique_ptr<ButtonCL>(new ButtonDevastatorCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonTankCL(1, 1, 10, false, false)));
    menu.push_back(std::unique_ptr<ButtonCL>(new ButtonTrikeCL(1, 1, 10, false, false)));

    SoundManager soundManager;
    soundManager.playMusik("atreides");

    Camera camera(m_initialPos);
    Engine engine(camera, map, menu, textureManager, soundManager, queueNb, queueB);
    RateController frameRate(30);
    frameRate.start();
    while (engine.IsRunning()) {
        engine.Events();
        engine.Update();
        engine.Render(renderer);
        frameRate.finish();
    }

    soundManager.clean();

    sendThread.stop();
    recvThread.stop();
    sendThread.join();
    recvThread.join();
}

void Client::iniciar(){
    std::vector<std::vector<char>> map = m_protocol.recvMap(m_socket);
    std::cout << "Mapa recibido..." << std::endl;
    initSDL(this->m_socket,this->m_protocol,map);
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
    textureManager.load(BRAIDER, DATA_PATH "assets/Button/Raider.gif");
    textureManager.load(BDESVIATOR, DATA_PATH "assets/Button/Deviator.gif");
    textureManager.load(BTANK, DATA_PATH "assets/Button/Tank.gif");
    textureManager.load(BDEVASTATOR, DATA_PATH "assets/Button/Devastator.gif");
    textureManager.load(BHARVESTER, DATA_PATH "assets/Button/Harvester.gif");
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

    textureManager.load(LIFE, DATA_PATH "assets/Other/lp_small.png");
    textureManager.load(ENERGY, DATA_PATH "assets/Other/energy.png");
    textureManager.load(GOLD, DATA_PATH "assets/Other/gold.png");
    textureManager.load(VICTORY, DATA_PATH "assets/Status/victory.png");
    textureManager.load(DEFEAT, DATA_PATH "assets/Status/defeat.png");
}

Client::~Client() = default;

//-----------------------------------------------------------------------------
