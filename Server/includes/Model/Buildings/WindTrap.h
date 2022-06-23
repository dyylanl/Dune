#ifndef __WIND_TRAP_H__
#define __WIND_TRAP_H__

#include "Building.h"

class WindTrap : public Building {
public:
    WindTrap(const int x, const int y, int blockWidth, int blockHeight);
    ~WindTrap();
};

#endif	// __WIND_TRAP_H__
