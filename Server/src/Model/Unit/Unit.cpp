#include "../../../includes/Model/Unit/Unit.h"


Unit::Unit(const int x, const int y, const int speed) :
        speed(speed),
        pathToDestiny(),
        destiny(x, y),
        next_pos(x, y),
        pos(x,y) {}

Unit::~Unit() {}

bool Unit::canMove() {
    return true;
}

void Unit::setPath(std::stack<Position> path, Position destiny1) {
    pathToDestiny = path;
    this->destiny = destiny1;
    if (!path.empty()) {
        next_pos = pathToDestiny.top();
        pathToDestiny.pop();
        // state = (UnitState*)&Unit::moving;
    } else {
        next_pos = pos;
        // state = (UnitState*)&Unit::stopped;
    }
}

Position &Unit::getPosition() {
    return pos;
}
