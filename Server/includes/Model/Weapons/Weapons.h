#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "AssaultRifle.h"
#include "RocketLauncher.h"
#include "SmallCannon.h"
#include "Cannon.h"

class Weapons {
public:
    static const RocketLauncher rocketLauncher;
    static const AssaultRifle assaultRifle;
    static const SmallCannon smallCannon;
    static const Cannon cannon;
};

#endif	// __WEAPONS_H__
