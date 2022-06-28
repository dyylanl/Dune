#include "../../includes/Model/Player.h"
#include "../../../Common/includes/Exceptions/Exception.h"

Player::Player(InstanceId id, std::string house, std::string name) :
id(id),
house(house),
name(name) {}

void Player::addGold(int gold1) {
    if (gold+gold1<=gold_limit) {
        gold += gold1;
        this->news = true;
    }
}

void Player::subGold(int gold1) {
    if (gold1 > gold ) {
        throw Exception("No se puede gastar mas oro de lo q se tiene, bah si, pero aca no.\n");
    }
    gold -= gold1;
    this->news = true;
}

float Player::getEnergyFactor() {
    float energy_factor = consumedEnergy < generatedEnergy ? 1 : (float)consumedEnergy / (float)generatedEnergy;
    return energy_factor;
}

void Player::addBuilding(Building *building) {
    buildings.push_back(building);
    //building->setPlayer(this);
}

bool Player::hasNews() {
    bool ret = news;
    this->news = false;
    return ret;
}

bool Player::operator==(const Player &other) const {
    return this->id == other.id;
}

void Player::addUnit(Unit *unit) {
    units.push_back(unit);
    //unit->setPlayer(*this);
}
