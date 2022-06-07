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

//-----------------------------------------------------------------------------

class Client {
private:
    std::string ip;
    std::string port;
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

    //-----------------------------------------------------------------------------

    /* Destructor */
    ~Client();
};

//-----------------------------------------------------------------------------

#endif  // __CLIENT_H__
