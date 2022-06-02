#include "../../../includes/Model/Units/Unit.h"

Unit::Unit(int x, int y) : position(x, y) {}

Position Unit::getPosition() {
    return this->position;
}

bool Unit::canMove() {
    return true;
}

Unit::~Unit() = default;
