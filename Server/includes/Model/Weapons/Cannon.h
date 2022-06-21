#ifndef __CANNON_H__
#define __CANNON_H__

#include "Weapon.h"

class Cannon : public Weapon {
public:
    Cannon();
    ~Cannon();
    virtual int getInfantryBonus() const override;
    virtual int getVehicleBonus() const override;
    virtual int getBuildingBonus() const override;
};

#endif
