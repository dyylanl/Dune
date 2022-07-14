#ifndef DUNE_UNITDTO_H
#define DUNE_UNITDTO_H

#include <string>
#include <vector>
#include "../../defs.h"

struct UnitDTO {
    Id unit_id;
    InstanceId player_id;
    int pos_x, pos_y;
    int next_x, next_y;
    char type;
    int life;
    int selected;

    UnitDTO(Id unit_id1, InstanceId player_id1, int x1, int y1, int next_x1, int next_y1, char unit_type, int life1, int selected1) :
    unit_id(unit_id1),
    player_id(player_id1),
    pos_x(x1),
    pos_y(y1),
    next_x(next_x1),
    next_y(next_y1),
    type(unit_type),
    life(life1),
    selected(selected1)
    {}

};


#endif //DUNE_UNITDTO_H
