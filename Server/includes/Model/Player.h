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
    InstanceId id;
    std::string house;
    std::string playerName;

public:
    int generatedEnergy;
    int consumedEnergy;
    int gold;
    int gold_limit;
    bool can_train;
    int status; // 1:gano 2:perdio 3:sige
    
    std::vector<Building*> buildings;
    std::vector<Unit*> units;
    ConstructionCenter* construction_center;
    std::vector<Unit*>& getTrainedUnits(Map& map);

    explicit Player(InstanceId id, ConstructionCenter *construction_center);
    void addGold(int gold_to_add);
    void subGold(int gold_to_sub);
    float getEnergyFactor();

    void addBuilding(Building* building);
    void addUnit(Unit* unit);

    void cleanDeads();
    Building * getClosestBuilding(Position pos, Building::BuildingType type);
    bool hasBuilding(Building& building);
    bool hasBuilding(Building::BuildingType buildingType);
    ConstructionCenter* getConstructionCenter();
    bool lose();
    bool isDefeated();
    InstanceId getId() const;
    std::string& getHouse();
    bool operator==(const Player& other) const;
    Position getBarrackPosition();
    void clean();
    bool canTrainUnits();


};

#endif  // __PLAYER_H__
