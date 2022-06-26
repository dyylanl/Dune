#include <stack>
#include "../../../includes/Model/Units/Offensive.h"
#include "../../../includes/Model/Weapons/Weapon.h"

Offensive::Offensive(const int x, const int y, const int hitPoints, const int range, const Weapon &weapon,
                             const int speed, const int cost) :
        Unit(x, y, hitPoints, speed, cost),
        Attacker(weapon, range) {}
//        ,attacking(false)



Position& Offensive::getVictimPosition() {
    return this->victim_pos;
}
