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
////////////////////////////////////////
class Game {
private:

    

    std::map<Id,MapDTO> maps_dto_init;
    
    /*
     * Contiene todas las partidas creadas por los users
     * clave: nombre del mapa
     * valor: mapa
     */
    // std::map<std::string, Map*> maps_created;

    // {name_game:[current,req]}
    std::map<std::string, std::vector<int>> info_games;
    

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
     * Lockea el mutex e insterta el valor current y req en games
     * si es que hay una key = game_name.
     */
    void put(const std::string& game_name, int current, int req);
    /*
     * Retorna el valor asociado a la clave game_name si es
     * que existe. El contains() lockea el mutex.
     */
    std::vector<int> get(const std::string& game_name);
    /*
     * Agrega un jugador a la partida game_name si es
     * que esta partida no esta completa.
     */
    void addPlayer(const std::string& game_name);
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

    /*
    * Retorna un nuevo id de conexion.
    */
    InstanceId getConnectionId() {return next_id++;}

    // devuelve el mapa ascii creado ¿por que el game deberia devolver el mapa??
    //std::vector<std::vector<char>>& getMap(std::string name_game);

    // TODO: TERMINAR ID's de mapa
    // static Id getMapId(std::string name_game) {return 1;};
   
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