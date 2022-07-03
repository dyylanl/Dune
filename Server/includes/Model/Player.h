//
// Created by dypa on 19/06/22.
//

#ifndef DUNE_PLAYER_H
#define DUNE_PLAYER_H

#include <string>
#include "../defs.h"

class Building;

class Player {
private:
    InstanceId id;
    std::string house;
    std::string name;
public:
    int generatedEnergy;
    int consumedEnergy;
    int gold;
    int gold_limit;

    /*
    *   Constructor de jugador con un id, casa y nombre otorgado
    */
    Player(InstanceId id, std::string house, std::string name);

    /*
    *   Suma la cantidad de oro indicada por parametro al jugador
    */
    void addGold(int gold);

    /*
    *   Resta la cantidad de oro indicada por parametro al jugador
    */
    void subGold(int gold);

    /*
    *   Retorna la cantidad de energia que genero el jugador
    */
    float getEnergyFactor();

    /*
    *   Operador de comparacion
    */
    bool operator==(const Player& other) const;

    /*
    *   Getters
    */
    std::string getName() {return name;}
    int getId() {return id;}
    
};

#endif //DUNE_PLAYER_H
