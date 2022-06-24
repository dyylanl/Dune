#ifndef __MOVINGSTATE_H__
#define __MOVINGSTATE_H__

#include "UnitState.h"
#include "../Unit.h"

class MovingState : public UnitState {
public:
    virtual UnitState *makeAction(Map &map, Unit &unit) override;
};

#endif //__MOVINGSTATE_H__
