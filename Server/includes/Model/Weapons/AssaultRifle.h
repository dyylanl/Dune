#ifndef __ASSAULT_RIFLE_H__
#define __ASSAULT_RIFLE_H__

#include "Weapon.h"

class AssaultRifle : public Weapon {
public:
    AssaultRifle();
    ~AssaultRifle();

    virtual int getInfantryBonus() const override;
    virtual int getVehicleBonus() const override;
    virtual int getBuildingBonus() const override;
};

#endif
