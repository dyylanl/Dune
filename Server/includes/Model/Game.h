#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <mutex>
#include "../defs.h"
#include "DTOs/MapDTO.h"
#include "../../config/ConfigReader.h"
#include "../Control/NewConnection.h"
#include "../Control/Engine.h"
////////////////////////////////////////
class Game {
private:

    /*
    * Carga inicial de los mapas.yaml
    */
    std::map<Id,MapDTO> maps_dto_init;

    /*
    * Cada vez que se cree una partida se iniciara un Engine para manejar esa partida y unir los jugadores a esa partida
    */
    std::map<std::string,Engine*> games;


    std::mutex mutex;
    ConfigurationReader config;


    // ---------- METODOS ------------- //

    /*
     * Lockea el mutex, retorna true si el name ya existe.
     */
    bool contains(const std::string& game_name);

    /*
     * Retorna el valor asociado a la clave game_name si es
     * que existe. El contains() lockea el mutex.
     */
    std::vector<int> get(const std::string& game_name);


public:
    /*
        *   Recibe por parametro la ruta para cargar la configuracion del juego.
        *   Carga todos los mapas con la ruta que le proporciona el config.yaml
        *   A cada mapa le setea un id unico.
    */
    Game(std::string path_game_config);

    /*
     * Crea una partida con el id y nombre solicitado y agrega al jugador creador de la partida
     * retorna 0 si se pudo crear
     * retorna 1 si no se pudo (es decir, ya existe una partida con ese nombre)
     *
     */
    uint16_t createGameAndAcceptPlayer(Id id_map, const std::string& name_game, Socket peer, std::string name_player);

    /*
     * Inserta un jugador a la partida que eligio.
     * retorna 0 si lo pudo unir
     * retorna 1 si no lo pudo unir (es decir, esta completa esa partida o bien no existe)
     */
    uint16_t acceptPlayer(Socket peer, std::string name_player, std::string name_game);


    /*
     * Retorna una lista con formato [actuales, req, name_game]
     */
    std::vector<std::vector<std::string>> listGames();

    /*
    * Retorna todos los MapDTO que se cargaron en el servidor.
    */
    std::vector<MapDTO> getMapsLoads();

    /*
    *   Termina todas las partidas corriendo en el servidor-
    */
    void stop();

    /*
    *   Metodo para registrar la cantidad de jugadores en todas las partidas creadas
    */
    std::vector<std::vector<InstanceId>> getAllPlayers();

    /*
    *   Retorna false si la partida indicada esta empezada o aka completa, sino true.
    */
    bool acceptNewPlayer(std::string name_game);

    /*
    *   Elimina todas las partidas creadas
    */
    ~Game();

};


#endif  // GAME_H