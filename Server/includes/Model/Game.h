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
#include "../Model/Map.h"
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
    

    // --------------------------------------------------- //
    std::mutex mutex;
    InstanceId next_id;
    //Map map;
    //AStar aStar;
    // comandos
    ConfigurationReader game_config;

    /*
     * Lockea el mutex, retorna true si el name ya existe.
     */
    bool contains(const std::string& game_name);

    /*
     * Retorna el valor asociado a la clave game_name si es
     * que existe. El contains() lockea el mutex.
     */
    std::vector<int> get(const std::string& game_name);
    
    /*
     * Lockea el mutex e imprime por pantalla
     * el comienzo de la partida 'name'.
     */
    // void printStartGame(const std::string &name);

public:
    Game(int rate, ConfigurationReader reader);

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
    uint16_t acceptPlayer(NewConnection* new_player);

    /*
     * Retorna una lista con formato [nombre, actuales, req]
     */
    std::vector<std::string> listGames();

    Id getMapId(std::string name_game);
   
   // devuelve la cantidad de mapas cargados en el servidor
   std::vector<MapDTO> getMapsLoads();
   
    ~Game();




// ------------------ ESTO HAY QUE BORRARLO --------------- //
    void selectUnitInPos(int pos_x, int pos_y);
    void build(char build_type, int pos_x, int pos_y);
    void moveUnitSelecteds(const uint16_t i, const uint16_t i1);
    void createUnit(char unit_type);
    bool fullyGame(std::string name_game);
};


#endif  // GAME_H