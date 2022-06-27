#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <cstdio>

//-----------------------------------------------------------------------------
// Sistemas de SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../../Common/includes/Socket/Socket.h"
#include "../../Common/includes/Protocol.h"
#include "../src/Graphics/TextureManager.h"

//-----------------------------------------------------------------------------

enum TextureType: char {TRIKE, SONIC_TANK, RAIDER, DESVIATOR, TANK, DEVASTATOR, HARVESTER,
        LIGHT_INFANTRY, HEAVY_INFANTRY, FREMEN, SARDAUKAR,
        CONSTRUCTION_YARD, LIGHT_FACTORY, HEAVY_FACTORY,WIND_TRAP, REFINERY, SILO, BARRACK, PALACE,
        BTRIKE, BSONIC_TANK, BRAIDER, BDESVIATOR, BTANK, BDEVASTATOR, BHARVESTER,
        BLIGHT_INFANTRY, BHEAVY_INFANTRY, BFREMEN, BSARDAUKAR,
        BCONSTRUCTION_YARD, BLIGHT_FACTORY, BHEAVY_FACTORY, BWIND_TRAP, BREFINERY, BSILO, BBARRACK, BPALACE,
        MENU, ARENA, CIMA, DUNA, PRECIPICIO, ROCA};

class Client {
    Socket socket;
    Protocol protocol;
public:
    Client();
    Client(std::string ip1, std::string port1); 
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;

    void launch();

    void crear_partida( std::string nombre_jugador,  std::string  nombre_partida);

    int obtener_numero_casa(const std::string& casa);

    void enviar_cant_jugadores(int cantidad);

    void enviar_accion(std::string comando);

    void enviar_nombre_jugador(std::string nombre_jugador);

    void enviar_nombre_partida(std::string nombre_partida);

    //std::vector<std::string> listar_partidas();

    std::vector<std::vector<std::string>> listar_mapas();

    void enviar_map_id(int map_id);

    void enviar_nombre_y_comando(const std::string& nombre_jugador,std::string comando);

    int recibir_respuesta();

    bool partida_iniciada();

    ~Client();

    /*void crearUnidad();*/

    void loadTextures(TextureManager &textureManager, SDL2pp::Renderer &renderer) const;

    void initSDL(Socket &aSocket, Protocol &aProtocol, std::vector<std::vector<char>> &map) const;
};

//-----------------------------------------------------------------------------

#endif  // __CLIENT_H__
