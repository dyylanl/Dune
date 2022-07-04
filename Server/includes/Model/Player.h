#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>
#include <functional>
#include "Buildings/ConstructionCenter.h"
#include "Map.h"
#include "Units/Unit.h"


class Player {
private:
    const int id;
    std::string house;
    std::string playerName;
    bool news;

public:     // El cliente sólo debería tenerse a su propio player disponible
    int generatedEnergy; // Se sumara durante el constructor de la trampa de viento y se restara durante su destructor
    int consumedEnergy; // se suma cuando se construye un edificio, se resta cuando se destruye
    int gold;   // Se restara durante los constructores
    int gold_limit; // Se sumara dentro del constructor de la refineria o el silo

    std::vector<Building*> buildings;
    ConstructionCenter* construction_center;

    std::vector<Unit*>& getTrainedUnits(Map& map);

    explicit Player(int id, ConstructionCenter &construction_center,
                    const std::string& house, const std::string& playerName);

    void addGold(int gold_to_add);
    void subGold(int gold_to_sub);
    float getEnergyFactor();

    void addBuilding(Building* building);
    void cleanDeadBuildings();

    Building * getClosestBuilding(Position pos, Building::BuildingType type);
    bool hasBuilding(Building& building);
    bool hasBuilding(Building::BuildingType buildingType);

    ConstructionCenter& getConstructionYard();

    bool lose();

    bool isDefeated();

    void trainUnits();
    void constructBuildings();

    int getId() const;
    std::string& getHouse();

    bool operator==(const Player& other) const;

    void sellBuilding(Building* building);

    bool hasNews();

    Position getBarrackPosition();
};

#endif  // __PLAYER_H__
