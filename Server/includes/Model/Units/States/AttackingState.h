#ifndef __ATTACKINGSTATE_H__
#define __ATTACKINGSTATE_H__

#include "UnitState.h"
#include "../Unit.h"

class AttackingState : public UnitState {
public:
    virtual UnitState *makeAction(Map &map, Unit &unit) override;
    virtual bool isAttacking() override;
};

#endif //__ATTACKINGSTATE_H__
