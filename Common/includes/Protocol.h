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
#include "../../Server/includes/Model/Map.h"

class Protocol {
private:
    bool was_closed;

    /*
     * Retorna el largo del nombre (2 bytes en little-endiann).
     */
    uint16_t recvNameLen(Socket &socket);
    
public:
    Protocol();
    ~Protocol();

    /*
     * Retorna 1 o 2 bytes respectivamente
     */
    uint8_t recvOneByte(Socket &socket);
    uint16_t recvTwoBytes(Socket &socket);

    /*
    *   Retorna true si se pudo enviar - 
    */
    bool sendOneByte(Socket &socket, uint8_t data);
    bool sendTwoBytes(Socket &socket, uint16_t data);

    /*
     * Envio de DTO's
     */
    void sendUnit(Socket &socket, UnitDTO unit);
    void sendBuild(Socket &socket, BuildingDTO build);

    /*
     * Metodos q usa el run del client
     */
    void recvCountObject(Socket &socket, int &size);
    void recvType(Socket &socket, char &type);

    void recvBuild(Socket &socket, int &id, char &player, int &posX, int &posY, int &life);
    void recvUnit(Socket &socket, int &id, char &player, bool &selectStatus, int &posX, int &posY, int &posActX,
                  int &posActY, int &life, bool &action);

    /*
     * Recibe una posicion
     */
    uint16_t recvPosition(Socket &socket);

    void sendInitGame(Socket &socket);
    bool recvInitGame(Socket &socket);
    void sendCreateGameInvalid(Socket &socket);
    void sendAcceptPlayerInvalid(Socket &socket);


    /*
     * Finaliza la comunicacion con el protocolo.
     */
    void close();

    /*
     * Retorna el tipo de comando (unirse, listar o crear)
     */
    uint8_t recvCommand(Socket &socket);

    /*
     * Envia la respuesta al comando (0 exito, 1 error)
     */
    bool sendResponse(Socket &socket, int resp);

    /*
     * Retorna un string de longitud name_long.
     */
    std::string recvName(Socket &socket);

    /*
     * Retorna el tipo de casa (0 Harkonnen, 1 Atreides y 2 Ordos)
     */
    uint8_t recvHouse(Socket &socket);
    
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
    uint8_t recvResponse(Socket &socket);

    /*
     * Envia una lista con el formato. (cantidad de elementos, (actuales, requeridos, longitud_nombre, nombre) ... ( , , , ,))
     */
    void sendGameList(Socket &socket, const std::vector<std::vector<std::string>>& list);

    /*
     * Retorna una lista con el formato (actuales, requeridos, nombre).
     */
    std::vector<std::vector<std::string>> recvGameList(Socket &socket);

    /*
     * Se envia una sola vez, con cada cliente nuevo.
     * Envia filas y columnas del mapa y luego cada terreno del mapa.
     */
    static void sendMap(Socket &socket, std::vector<std::vector<char>>& map) ;

    static std::vector<std::vector<char>> recvMap(Socket &socket);

    bool sendName(Socket &socket, std::string name);

    void sendCountObject(Socket &socket, int &countObject);

    void recvObjectType(Socket &socket, char &i);

    void sendCommandSelect(Socket &socket, char &action, int &id);

    void sendCommandMove(Socket &socket, char &action, int &id, int &posX, int &posY);

    void sendCommandBuildBuilding(Socket &socket, char &action, char &build, int &posX, int &posY);

    void sendMapsCreated(Socket &socket, std::vector<MapDTO> maps);

    std::vector<std::vector<std::string>> recvMapsCreated(Socket &socket);

    // Servidor le envia al cliente que se pudo conectar correctamente
    void sendEstablishConnection(Socket &socket);

    bool recvEstablishConnection(Socket &socket);

    void sendCommandCreateUnit(Socket &socket, char &action, char &unitType);

};


#endif  // PROTOCOLO_H