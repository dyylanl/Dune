#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <mutex>
////////////////////////////////////////
#include "../defs.h"
#include "Map.h"
#include "AStar.h"
#include "../Control/NewConnection.h"
#include "../../config/GameConfig.h"
#include "../../config/ConfigReader.h"

class Game {
private:
    std::map<Id,Map> maps_init;
    /*
     * Contiene todas las partidas creadas por los users
     * clave: nombre del mapa
     * valor: mapa
     */
    std::map<std::string, Map> maps;
    /*
     * aca esta toda la informacion actualizada para enviarsela al cliente y hacer todos los chequeos
     * por lo tanto al ser el unico recurso compartido solo uso el mutex en este map
     */
    std::map<std::string, std::vector<int>> games;
    /*
     * clave: nombre de la partida
     * valor: jugadores en esa partida
     * {duelo 3vs3: [dylan,ricardo,fede,fede,mateo,pepe], solo: [alone], ...}
     */
    std::map<std::string,std::vector<Player*>> players;

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
     * Crea una partida {name:[1,req,id_mapa]}
     * Return: 0 exito 1 error
     *
     */
    uint16_t createGame(int req,Id id_map, const std::string& name);
    /*
     * Inserta un jugador a la partida name.
     */
    uint16_t acceptPlayer(const std::string& name);
    /*
     * Retorna una lista con formato [nombre, actuales, req]
     */
    std::vector<std::string> listGames();

    /*
     * Retorna un id de instancia nuevo
     */
    InstanceId newConnection(NewConnection* connection);

    std::stack<Position> makePath(Unit& unit, Position pos_end);

    InstanceId getConnectionId() {return next_id++;}

    std::vector<std::vector<char>>& getMap(std::string name_game);

    // TODO: TERMINAR ID's de mapa
    static Id getMapId(std::string name_game) {return 1;};


    ///////////// comandos ////////////
    /*
     * si hay una unidad en pos_x pos_y entonces la agrega a la lista de unidades selecteds
     */
    void selectUnitInPos(int pos_x, int pos_y);

    /*
     * construye un edificio del tipo type en la posicion indicada si es que se puede
     */
    void build(char build_type, int pos_x, int pos_y);

    void moveUnitSelecteds(const uint16_t i, const uint16_t i1);

    void createUnit(char unit_type);
};


#endif  // GAME_H