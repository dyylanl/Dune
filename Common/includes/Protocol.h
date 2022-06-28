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
#include "../../Server/includes/Model/Units/Unit.h"
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
     * Envia la informacion requerida para crear una partida.
     */
    void createGame(Socket &socket, uint16_t house,
                    const std::string& name, int req);


    void sendInitGame(Socket &socket);
    bool recvInitGame(Socket &socket);
    void sendCreateGameInvalid(Socket &socket);
    void sendAcceptPlayerInvalid(Socket &socket);


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
    bool sendResponse(Socket &socket, int resp);
    /*
     * Retorna un string de longitud name_long.
     */
    std::string recvName(Socket &socket);
    /*
     * Retorna el tipo de casa (0 Harkonnen, 1 Atreides y 2 Ordos)
     */
    uint16_t recvHouse(Socket &socket);
    
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
    void sendGameList(Socket &socket, const std::vector<std::vector<std::string>>& list);
    /*
     * Retorna una lista con el formato (actuales, requeridos, nombre).
     */
    std::vector<std::vector<std::string>> recvGameList(Socket &socket);
    /*
     *
     */
    void recvCreate(Socket &socket, int &house, int &req, std::string &name);
    /*
     *
     */
    void recvJoin(Socket &socket, std::string &name);

    /*
     * Envia el tipo de unidad
     */
    void sendUnit(Socket &socket, int type);
    /*
     * Envia la posicion en orden x y luego y
     */
    void sendPosition(Socket &socket, unsigned x, unsigned y);
    /*
     * Retorna el tipo de unidad (char)
     */
    char recvUnitType(Socket &skt);
    /*
     * Retorna una posicion
     */
    static std::vector<int> recvPosition(Socket &skt);

    void sendBuild(Socket &socket, int build, int posX, int posY);

    void operationRecv(Socket &socket, char &operation);

    char typeUnidRecv(Socket &socket);

    int idUnidRecv(Socket &socket);

    /*
     * Se envia una sola vez, con cada cliente nuevo.
     * Envia filas y columnas del mapa y luego cada terreno del mapa.
     */
    static void sendMap(Socket &socket, std::vector<std::vector<char>>& map) ;

    static std::vector<std::vector<char>> recvMap(Socket &socket);
    void sendName(Socket &socket, std::string name);

    void
    recvUnit(Socket &socket, int &id, char &player, bool &selectStatus, int &posX, int &posY, int &posActX,
             int &posActY, int &life, bool &action);

    void recvType(Socket &socket, char &type);

    void sendType(Socket &socket, int &actionType);

    void sendAction(Socket &socket, int &id, int &posX, int &posY);

    void sendId(Socket &socket, int &id);

    void recvCountObject(Socket &socket, int &size);

    void recvBuild(Socket &socket, int &id, char &player, int &posX, int &posY, int &life);

    void sendCountObject(Socket &socket, int &countObject);

    void enviar(Socket &socket);

    void recvObjectType(Socket &socket, char &i);

    void recvBotton(Socket &socket, int &id, char &player, int &constructionTime, bool &selectStatus, bool &ready);

    void sendCommandSelect(Socket &socket, char &action, int &id);

    void sendCommandMove(Socket &socket, char &action, int &id, int &posX, int &posY);

    void sendCommandBuildBuilding(Socket &socket, char &action, char &build, int &posX, int &posY);

    /*
     *
     */
    std::vector<std::string> recvMapsId(Socket &socket);

    void sendMapsId(Socket &socket, std::vector<std::string> maps_id);

    void sendMapsCreated(Socket &socket, std::vector<MapDTO> maps);

    std::vector<std::vector<std::string>> recvMapsCreated(Socket &socket);

    // Servidor le envia al cliente que se pudo conectar correctamente
    void sendEstablishConnection(Socket &socket);

    bool recvEstablishConnection(Socket &socket);

};


#endif  // PROTOCOLO_H