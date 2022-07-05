#ifndef __ROCKET_LAUNCHER_H__
#define __ROCKET_LAUNCHER_H__

#include "Weapon.h"

class RocketLauncher : public Weapon {
public:
    RocketLauncher();
    ~RocketLauncher();

    virtual int getInfantryBonus() const override;
    virtual int getVehicleBonus() const override;
    virtual int getBuildingBonus() const override;
};

#endif
