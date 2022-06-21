#ifndef __SPICE_REFINERY_H__
#define __SPICE_REFINERY_H__

#include "Building.h"
#include "../Player.h"

class Refinery : public Building {
public:
    Refinery(const int x, const int y, int blockWidth, int blockHeight);
    ~Refinery();

    bool load(Player &player);

    virtual int getCapacity() override;
private:
    int capacity;
};

#endif
