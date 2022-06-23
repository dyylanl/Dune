#ifndef __Offensive_H__
#define __Offensive_H__


#include "Unit.h"
#include "Attacker.h"


class Offensive : public Unit, public Attacker {
public:
    Offensive(const int x, const int y, const int hitPoints, const int range,
                  const Weapon &weapon, const int speed, const int cost);
    Position& getVictimPosition();
private:
    Position victim_pos;
    bool news;

};

#endif //__Offensive_H__
