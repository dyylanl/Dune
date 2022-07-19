#ifndef DUNE_PLAYERDTO_H
#define DUNE_PLAYERDTO_H

#include <string>
#include <vector>
#include "../../defs.h"

struct PlayerDTO {
    InstanceId player_id;
    int gold;
    int energy;
    uint8_t status;

    PlayerDTO(InstanceId player_id1, int gold1, int energy1, uint8_t status1) : player_id(player_id1), gold(gold1), energy(energy1), status(status1) {}
};


#endif //DUNE_PLAYERDTO_H
