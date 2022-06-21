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

//-----------------------------------------------------------------------------

class Client {
private:
    Socket socket;
    Protocol protocol;
public:
    /* Constructor */
    Client(std::string ip, std::string port);

    /* Deshabilitamos el constructor por copia. */
    Client(const Client&) = delete;

    /* Deshabilitamos el operador= para copia.*/
    Client& operator=(const Client&) = delete;

    /* Deshabilitamos el constructor por movimiento. */
    Client(Client&& other) = delete;

    /* Deshabilitamos el operador= para movimiento. */
    Client& operator=(Client&& other) = delete;

    //-----------------------------------------------------------------------------
    // Métodos de la API pública

    /* Ejecuta el cliente */
    void launch();

    void crear_partida(const std::string& nombre_jugador, const std::string&  nombre_partida, int cantidad_jugadores);

    int obtener_numero_casa(const std::string& casa);

    void enviar_cant_jugadores(int cantidad);

    void enviar_accion(std::string comando);

    void enviar_nombre_jugador(std::string nombre_jugadar);

    void enviar_nombre_partida(std::string nombre_partida);

    std::vector<std::string> listar_partidas();

    //-----------------------------------------------------------------------------

    /* Destructor */
    ~Client();

    void crearUnidad();
};

//-----------------------------------------------------------------------------

#endif  // __CLIENT_H__
