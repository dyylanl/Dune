#include <iostream>
#include "../../includes/Model/Player.h"
#include "../../config/GameConfiguration.h"
#include "../../includes/Model/Buildings/Barrack.h"

Player::Player(InstanceId id1, ConstructionCenter *construction_center):
        id(id1),
        news(true),
        generatedEnergy(GameConfiguration::getConfig().initialMaxEnergy),
        consumedEnergy(GameConfiguration::getConfig().initialEnergy),
        gold(GameConfiguration::getConfig().initialGold),
        gold_limit(GameConfiguration::getConfig().initialGold),
        construction_center(construction_center)
        {
            construction_center->setPlayer(this);
        }

bool Player::operator==(const Player &other) const {
    return this->id == other.id;
}

void Player::addGold(int gold_to_add) {
    gold += gold_to_add;
    this->news = true;
}

void Player::subGold(int gold_to_sub) {
    // if (gold_to_sub > gold ) throw error -> Ver que hacer
    gold -= gold_to_sub;
    this->news = true;
}

float Player::getEnergyFactor() {
    float energy_factor = consumedEnergy < generatedEnergy ? 1 : (float)consumedEnergy / (float)generatedEnergy;
    return energy_factor;
}

void Player::addBuilding(Building *building) {
    buildings.push_back(building);
    building->setPlayer(this);
    if (building->is(Building::WIND_TRAP)) {
        this->generatedEnergy += building->energy;
    } else {
        this->consumedEnergy += building->energy;
    }
    this->gold_limit += building->getCapacity();
    this->subGold(building->cost);
}

//bool Player::hasBuilding(Building *building) {
//    return std::find(buildings.begin(), buildings.end(), building) != buildings.end();
//}

Building *Player::getClosestBuilding(Position pos, Building::BuildingType type) {
    for (auto& b : buildings) {
        if ( b->is(type) ) {
            return b;
        }
    }
    return nullptr;
}
/*
void Player::trainUnits() {
    trainingCenter.trainUnits(buildings);
}

void Player::constructBuildings() {
    buildingCenter.construct();
}
*/

bool Player::lose() {
//    return this->lose;
    return this->construction_center == nullptr;
}

InstanceId Player::getId() const {
    return id;
}

std::string& Player::getHouse() {
    return this->house;
}
ConstructionCenter &Player::getConstructionCenter() {
    return *construction_center;
}

bool Player::hasBuilding(Building& building) {
    if (construction_center != nullptr) {
        if (building == *construction_center) {
            return true;
        }
    }
    for (auto& b : buildings) {
        if (*b == building) {
            return true;
        }
    }
    return false;
}

bool Player::hasBuilding(Building::BuildingType buildingType) {
    bool buildingTypeFound = false;
    unsigned i = 0;
    while ((!buildingTypeFound) && (i < this->buildings.size())) {
        buildingTypeFound = this->buildings[i]->is(buildingType);
        i++;
    }
    return buildingTypeFound;
}

void Player::cleanDeadBuildings() {
    if (Attackable::isDead(this->construction_center)) {
        this->construction_center = nullptr;
    }
    std::vector<Building*>::iterator it = buildings.begin();
    while (it != buildings.end()) {
        if (Attackable::isDead(*it)) {
            if ((*it)->is(Building::WIND_TRAP)) {
                this->generatedEnergy -= (*it)->energy;
            } else {
                this->consumedEnergy -= (*it)->energy;
            }
            this->gold_limit -= (*it)->getCapacity();
            news = true;
            it = buildings.erase(it);
        } else {
            it++;
        }
    }
}
/*
void Player::sellBuilding(Building* building) {
    std::vector<Building*>::iterator it = buildings.begin();
    while (it != buildings.end()) {
        if ((*it) == building) {
            gold += building->cost * float(building->getLife()) / float(building->getInitialLife()) * 0.9;
            building->demolish();
            news = true;
            break;
        } else {
            it++;
        }
    }
}*/

bool Player::hasNews() {
    return ( news);
}

bool Player::isDefeated(){
    if (this->construction_center == nullptr)
        return true;
    return (this->construction_center->getLife()<=0);
}

Position Player::getBarrackPosition() {
    Position pos(-1,-1);
    for(auto& build : buildings) {
        if (build->getType() == BARRACKS_KEY) {
            pos.x = build->getPosition().y;
            pos.y = build->getPosition().x;
        }
    }
    return pos;
}

void Player::clean() {
    delete construction_center;
    for (auto* build : buildings) {
        delete build;
    }
    for (auto* unit : units) {
        delete unit;
    }
}

bool Player::canTrainUnits() {
    for(auto& build : buildings) {
        if (build->getType() == BARRACKS_KEY) {
            return true;
        }
    }
    return false;
}