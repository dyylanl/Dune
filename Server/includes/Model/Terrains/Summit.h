#ifndef __SUMMIT_H__
#define __SUMMIT_H__

#include "Terrain.h"

class Summit : public Terrain {
public:
    Summit();
    void buildOn(Building* building) override;
};

#endif	//__SUMMIT_H__
