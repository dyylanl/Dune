#ifndef __PRECIPICE_H__
#define __PRECIPICE_H__

#include "Terrain.h"

class Precipice : public Terrain {
public:
    Precipice();
    void buildOn(Building* building) override;
};

#endif //__PRECIPICE_H__
