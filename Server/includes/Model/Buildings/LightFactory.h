#ifndef __LIGHT_FACTORY_H__
#define __LIGHT_FACTORY_H__

#include "Building.h"

class LightFactory : public Building {
public:
    LightFactory(int player_id, const int x, const int y, int blockWidth, int blockHeight);
    ~LightFactory();
};

#endif	// __LIGHT_FACTORY_H__
