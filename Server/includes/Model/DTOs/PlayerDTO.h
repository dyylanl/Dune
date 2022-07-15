#ifndef DUNE_PLAYERDTO_H
#define DUNE_PLAYERDTO_H

#include <string>
#include <vector>
#include "../../defs.h"

struct PlayerDTO {
    InstanceId player_id;
    int gold;
    int energy;

    PlayerDTO(InstanceId player_id1, int gold1, int energy1) : player_id(player_id1), gold(gold1), energy(energy1) {}
};


#endif //DUNE_PLAYERDTO_H
