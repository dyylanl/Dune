//
// Created by dypa on 04/07/22.
//

#ifndef DUNE_PALACE_H
#define DUNE_PALACE_H

#include "Building.h"

class Palace : public Building {
public:
    Palace(const int x, const int y, int blockWidth, int blockHeight);
    ~Palace();
};


#endif //DUNE_PALACE_H
