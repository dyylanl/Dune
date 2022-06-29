#ifndef DUNE_BUILDINGDTO_H
#define DUNE_BUILDINGDTO_H

#include <string>
#include <vector>
#include "../../defs.h"

struct BuildingDTO {
    Id build_id;
    int pos_x, pos_y;
    int width, height;
    char type;
    int life;
};


#endif //DUNE_MAPDTO_H
