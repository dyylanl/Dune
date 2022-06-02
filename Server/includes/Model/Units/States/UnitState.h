#ifndef __UNITSTATE_H__
#define __UNITSTATE_H__

class Map;
class Unit;

class UnitState {
public:
    virtual UnitState *makeAction(Map &map, Unit &unit) = 0;
    virtual bool isAttacking();
    virtual bool isTraining();
};

#endif	// __UNITSTATE_H__
