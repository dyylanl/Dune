#ifndef DUNE_UNITDTO_H
#define DUNE_UNITDTO_H

#include <string>
#include <vector>
#include "../../defs.h"

struct UnitDTO {
    Id unit_id;
    uint8_t player_id;
    int pos_x, pos_y;
    char type;
    int life;
    float speed;
    int selected = 0;
};


#endif //DUNE_UNITDTO_H
