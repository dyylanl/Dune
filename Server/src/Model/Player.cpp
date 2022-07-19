#include <iostream>
#include "../../includes/Model/Player.h"
#include "../../config/GameConfiguration.h"
#include "../../includes/Model/Buildings/Barrack.h"

Player::Player(InstanceId id1, ConstructionCenter *construction_center):
        id(id1),
        generatedEnergy(GameConfiguration::getConfig().initialMaxEnergy),
        consumedEnergy(GameConfiguration::getConfig().initialEnergy),
        gold(GameConfiguration::getConfig().initialGold),
        gold_limit(GameConfiguration::getConfig().initialGold),
        can_train(false),
        status(3),
        construction_center(construction_center)
        {
            construction_center->setPlayer(this);
        }

bool Player::operator==(const Player &other) const {
    return this->id == other.id;
}

void Player::addGold(int gold_to_add) {
    gold += gold_to_add;
}

void Player::subGold(int gold_to_sub) {
    gold -= gold_to_sub; // no hace falta lanzar excepcion pq se chequea q el player tenga oro > gold_to_sub
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
    if (building->is(Building::BARRACKS)) {
        can_train = true;
    }
    this->gold_limit += building->getCapacity();
    this->subGold(building->cost);
}

// todo: aca chequear si tiene el edificio correspondiente a esa unidad
void Player::addUnit(Unit* unit) {
    units.push_back(unit);
}


Building *Player::getClosestBuilding(Position pos, Building::BuildingType type) {
    for (auto& b : buildings) {
        if ( b->is(type) ) {
            return b;
        }
    }
    return nullptr;
}

bool Player::lose() {
    return (this->construction_center == nullptr);
}

InstanceId Player::getId() const {
    return id;
}

std::string& Player::getHouse() {
    return this->house;
}

ConstructionCenter* Player::getConstructionCenter() {
    return construction_center;
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

void Player::cleanDeads() {
    if (isDefeated()) {
        this->status = 2;
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
            it = buildings.erase(it);
        } else {
            it++;
        }
    }

    std::vector<Unit*>::iterator itrU = units.begin();
    while (itrU != units.end()) {
        if (Attackable::isDead(*itrU)) {
            itrU = units.erase(itrU);
        } else {
            itrU++;
        }
    }
}

bool Player::isDefeated(){
    if (this->construction_center == nullptr) {
        this->status = 2;
        return true;
    } if (this->construction_center->getLife() <= 0){
        this->status = 2;
        return true;
    }
    return false;
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
    for (Building *build: buildings) {
        build->demolish();
    }
    for (Unit *unit: units) {
        unit->kill();
    }
}

bool Player::canTrainUnits() {
    return can_train;
}