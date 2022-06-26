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

class Client {
public:
    Client();
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;

    void launch();
/*
    void crear_partida(const std::string& nombre_jugador, const std::string&  nombre_partida, int cantidad_jugadores);

    int obtener_numero_casa(const std::string& casa);

    void enviar_cant_jugadores(int cantidad);

    void enviar_accion(std::string comando);

    void enviar_nombre_jugador(std::string nombre_jugadar);

    void enviar_nombre_partida(std::string nombre_partida);

    std::vector<std::string> listar_partidas();*/
    ~Client();

    /*void crearUnidad();*/

    void loadTextures(TextureManager &textureManager) const;

    void initSDL(Socket &socket, Protocol &protocol, std::vector<std::vector<char>> &map) const;
};

//-----------------------------------------------------------------------------

#endif  // __CLIENT_H__
