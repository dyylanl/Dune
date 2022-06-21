#ifndef __HEAVY_FACTORY_H__
#define __HEAVY_FACTORY_H__

#include "Building.h"

class HeavyFactory : public Building {
public:
    HeavyFactory(const int x, const int y, int blockWidth, int blockHeight);
    ~HeavyFactory();
};

#endif
