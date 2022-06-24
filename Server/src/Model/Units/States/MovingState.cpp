#include "../../../../includes/Model/Units/States/MovingState.h"

UnitState *MovingState::makeAction(Map &map, Unit &unit) {
    if (unit.move(map)) {
        return this;
    } else {
        return (UnitState*)&Unit::stopped;
    }
}
