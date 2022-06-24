//
// Created by dypa on 19/06/22.
//

#ifndef DUNE_PLAYER_H
#define DUNE_PLAYER_H

#include <string>
#include "Buildings/Building.h"
#include "../defs.h"
#include "Units/Unit.h"

class Building;

class Player {
private:
    InstanceId id;
    std::string house;
    std::string name;
    //YAMLReader reader;
    bool news; // flag para controlar si ejecuto cambios

public:
    // oro y energia
    int generatedEnergy;
    int consumedEnergy;
    int gold;
    int gold_limit;

    // edificaciones que le pertenecen al player
    std::vector<Building*> buildings;
    // unidades que le pertenecen al player
    std::vector<Unit*> units;

    Player(InstanceId id, std::string house, std::string name);
    void addGold(int gold);
    void subGold(int gold);
    float getEnergyFactor();
    bool operator==(const Player& other) const;

    // agrega a la lista de edificaciones del jugador la nueva construccion
    void addBuilding(Building* building);

    void addUnit(Unit* unit);

    std::string getName() {return name;}

    int getId() {return id;}

    // una vez q se pregunta si tuvo novedades se setea en falso el new
    bool hasNews();

};

#endif //DUNE_PLAYER_H
