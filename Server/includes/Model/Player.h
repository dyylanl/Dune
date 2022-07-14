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

public:

    int generatedEnergy;
    int consumedEnergy;
    int gold;
    int gold_limit;

    std::vector<Building*> buildings;
    std::vector<Unit*> units;
    ConstructionCenter* construction_center;

    std::vector<Unit*>& getTrainedUnits(Map& map);

    explicit Player(InstanceId id, ConstructionCenter *construction_center);

    void addGold(int gold_to_add);
    void subGold(int gold_to_sub);

    float getEnergyFactor();
    void addBuilding(Building* building);

    void cleanDeadBuildings();

    Building * getClosestBuilding(Position pos, Building::BuildingType type);
    bool hasBuilding(Building& building);
    bool hasBuilding(Building::BuildingType buildingType);

    ConstructionCenter& getConstructionCenter();

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
    
    void clean();
};

#endif  // __PLAYER_H__
