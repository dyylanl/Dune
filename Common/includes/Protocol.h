#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include <arpa/inet.h>
#include <utility>
#include <string>
#include <atomic>
#include <vector>
#include <iostream>
//----------------------------------------//
#include "Socket/Socket.h"

class Protocol {
private:
    bool was_closed;

public:
    Protocol();
    ~Protocol();
    /*
     * Envia la informacion requerida para crear una partida.
     */
    void createGame(Socket &socket, uint16_t house,
                    const std::string& name, int req);
    /*
     * Envia la informacion requerida para unirse una partida.
     */
    void joinGame(Socket &socket, uint16_t house,
                  const std::string& name);
    /*
     * Envia la informacion requerida para listar la/s partida/s.
     */
    void listGames(Socket &socket);
    /*
     * Finaliza la comunicacion con el protocolo.
     */
    void close();
    /*
     * Retorna el tipo de comando (unirse, listar o crear)
     */
    uint16_t recvCommand(Socket &socket);
    /*
     * Envia la respuesta al comando (0 exito, 1 error)
     */
    void sendResponse(Socket &socket, int resp);
    /*
     * Retorna un string de longitud name_long.
     */
    std::string recvName(Socket &socket, uint16_t name_long);
    /*
     * Retorna el tipo de casa (0 Harkonnen, 1 Atreides y 2 Ordos)
     */
    uint16_t recvHouse(Socket &socket);
    /*
     * Retorna el largo del nombre (2 bytes en little-endiann).
     */
    uint16_t recvNameLen(Socket &socket);
    /*
     * Retorna la cantidad de jugadores actuales (1 byte)
     */
    uint16_t recvCurrent(Socket &socket);
    /*
     * Retorna la cantidad de jugadores requeridos (1 byte)
     */
    uint16_t recvReq(Socket &socket);
    /*
     * Retorna la respuesta a la ejecucion del comando (0 exito, 1 error)
     */
    uint16_t recvResponse(Socket &socket);
    /*
     * Envia una lista con el formato. (cantidad de elementos, (actuales, requeridos, longitud_nombre, nombre) ... ( , , , ,))
     */
    void sendGameList(Socket &socket, const std::vector<std::string>& list);
    /*
     * Retorna una lista con el formato (actuales, requeridos, nombre).
     */
    std::vector<std::string> recvGameList(Socket &socket);


    void recvCreate(Socket &socket, int &house, int &req, std::string &name);
    void recvJoin(Socket &socket, std::string &name);
};


#endif  // PROTOCOLO_H