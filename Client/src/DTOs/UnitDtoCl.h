//
// Created by dypa on 13/07/22.
//

#ifndef DUNE_UNITDTOCL_H
#define DUNE_UNITDTOCL_H

#include <cstdint>

struct UnitDtoCl {
    int unit_id;
    uint8_t player_id;
    int pos_x, pos_y;
    char type;
    int life;
    float speed;
    int selected;
};

#endif //DUNE_UNITDTOCL_H
