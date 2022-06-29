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
    ConfigurationReader game_config;

    /*
    *   Contiene informacion sobre todas las partidas creadas con un orden {nombre: [actuales,requeridos,map_id], ...}
    */
    std::map<std::string, std::vector<int>> info_games;


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
     * Crea una partida con el id y nombre solicitado
     * retorna 0 si se pudo crear
     * retorna 1 si no se pudo (es decir, ya existe una partida con ese nombre)
     *
     */
    uint16_t createGame(Id id_map, const std::string& name);

    /*
     * Inserta un jugador a la partida que eligio.
     * retorna 0 si lo pudo unir
     * retorna 1 si no lo pudo unir (es decir, esta completa esa partida o bien no existe)
     */
    uint16_t acceptPlayer(Socket &peer, std::string name_player, std::string name_game);


    /*
     * Retorna una lista con formato [actuales, req, name_game]
     */
    std::vector<std::vector<std::string>> listGames();

    /*
    * Retorna el id de mapa asociado a esa partida
    */
    Id getMapId(std::string name_game);
   
   /*
   * Retorna todos los MapDTO que se cargaron en el servidor.
   */
   std::vector<MapDTO> getMapsLoads();

    /*
    *   Termina todas las partidas corriendo en el servidor-
    */
   void stop();

   std::vector<std::vector<InstanceId>> getAllPlayers();
   

    ~Game();




// ------------------ ESTO HAY QUE BORRARLO --------------- //
    void selectUnitInPos(int pos_x, int pos_y);
    void build(char build_type, int pos_x, int pos_y);
    void moveUnitSelecteds(const uint16_t i, const uint16_t i1);
    void createUnit(char unit_type);
    bool fullyGame(std::string name_game);
};


#endif  // GAME_H