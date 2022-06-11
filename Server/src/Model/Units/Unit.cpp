#include "../../../includes/Model/Units/Unit.h"

Unit::Unit(int id, char type, int x, int y) : id(id), unitType(type), position(x, y) {}

Position Unit::getPosition() {
    return this->position;
}

bool Unit::canMove() {
    return true;
}

char Unit::getUnitType() {
    return unitType;
}

int Unit::getId() {
    return id;
}

void Unit::setPosition(Position pos) {
    this->position = pos;
}

Unit::~Unit() = default;
