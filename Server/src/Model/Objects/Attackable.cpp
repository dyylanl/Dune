#include "../../../includes/Model/Objects/Attackable.h"
#include <iostream>

Attackable::Attackable(const int life, const int x, const int y) :
        initial_life(life),
        life(life),
        pos(x, y) {}

int Attackable::getLife() {
    return life;
}

int Attackable::getInitialLife() {
    return initial_life;
}


void Attackable::reciveAttack(const Weapon &weapon) {
    std::cout << "Vida antes del ataque: " << life << std::endl;
    life -= weapon.getDammage();
    this->reciveBonusDammage(weapon);
    std::cout << "Vida despues del ataque: " << life << std::endl;
}

bool Attackable::isDead(const Attackable *unit) {
    if (!unit) {
        return true;
    }
    return (unit->life <= 0);
}

Position &Attackable::getPosition() {
    return pos;
}

void Attackable::setPosition(Position pos1) {
    this->pos = pos1;
}

Position& Attackable::getClosestPosition(Position& position) {
    return this->pos;
}

