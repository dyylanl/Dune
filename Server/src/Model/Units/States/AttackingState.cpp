#include "../../../../includes/Model/Units/States/AttackingState.h"

UnitState *AttackingState::makeAction(Map &map, Unit &unit) {
    return unit.makeAttack(map);
}

bool AttackingState::isAttacking() {
    return true;
}
