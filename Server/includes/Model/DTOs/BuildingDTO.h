#ifndef DUNE_BUILDINGDTO_H
#define DUNE_BUILDINGDTO_H

#include <string>
#include <vector>
#include "../../defs.h"
#include "../../types.h"

struct BuildingDTO {
    Id build_id;
    InstanceId player_id;
    int pos_x, pos_y;
    char type;
    int life;

    BuildingDTO(Id build_id1, InstanceId player_id1, int x1, int y1, char build_type1, int life1) :
                build_id(build_id1),
                player_id(player_id1),
                pos_x(x1),
                pos_y(y1),
                type(build_type1),
                life(life1)
                {}
};

#endif //DUNE_BUILDINGDTO_H
