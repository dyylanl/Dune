#include "../../../includes/Model/Weapons/Weapon.h"

Weapon::Weapon(int damage, int frecuency, int bonus) :
        damage(damage),
        frecuency(frecuency),
        bonus(bonus) {}

Weapon::~Weapon() {}

int Weapon::getDammage() const {
    return damage;
}

int Weapon::getFrecuency() const{
    return frecuency;
}
