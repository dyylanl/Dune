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
#include "../Control/YAMLReader.h"
#include "AStar.h"
#include "../Control/NewConnection.h"

class Game {
private:
    std::map<std::string, std::vector<int>> games;
    std::mutex mutex;
    InstanceId next_id;
    Map map;
    AStar aStar;
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
    Game(int rate, YAMLReader reader);
    /*
     * Crea una partida {name:[1,req]}
     */
    uint16_t createGame(int house, int req, const std::string& name);
    /*
     * Inserta un jugador a la partida name.
     */
    uint16_t acceptPlayer(const std::string& name);
    /*
     * Retorna una lista con formato [nombre, actuales, req]
     */
    std::vector<std::string> listGames();

    InstanceId newConnection(NewConnection* connection);

    std::stack<Position> makePath(Unit unit, Position pos_end);


    std::vector<std::vector<char>> getMap() {return this->map.getMap();}

};


#endif  // GAME_H