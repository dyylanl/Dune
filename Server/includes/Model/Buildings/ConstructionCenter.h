#ifndef __CONSTRUCTION_YARD_H__
#define __CONSTRUCTION_YARD_H__

#include "Building.h"

class ConstructionCenter : public Building {
public:
    ConstructionCenter(int player_id,const int x, const int y, int blockWidth, int blockHeight);
    ~ConstructionCenter();
};

#endif	// __CONSTRUCTION_YARD_H__
