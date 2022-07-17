#ifndef __SPICE_SILO_H__
#define __SPICE_SILO_H__

#include "Building.h"

class Silo : public Building {
public:
    Silo(int player_id,const int x, const int y, int blockWidth, int blockHeight);
    ~Silo();

    virtual int getCapacity() override;
private:
    int capacity;
};

#endif
