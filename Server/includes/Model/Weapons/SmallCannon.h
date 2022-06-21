#ifndef __SMALL_CANNON_H__
#define __SMALL_CANNON_H__

#include "Weapon.h"
/*
 * representa el 22m
 */
class SmallCannon : public Weapon {
public:
    SmallCannon();
    ~SmallCannon();
    virtual int getInfantryBonus() const override;
    virtual int getVehicleBonus() const override;
    virtual int getBuildingBonus() const override;
};

#endif	// __SMALL_CANNON_H__
