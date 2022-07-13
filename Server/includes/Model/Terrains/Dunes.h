#ifndef __DUNES_H__
#define __DUNES_H__

#include "Terrain.h"

class Dunes : public Terrain {
public:
    Dunes();
    void buildOn(Building* building) override;
};

#endif	//__DUNES_H__
