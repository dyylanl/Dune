#ifndef DUNE_SNAPSHOT_H
#define DUNE_SNAPSHOT_H

#include <vector>
#include "../../defs.h"
#include "BuildingDTO.h"
#include "UnitDTO.h"
#include "PlayerDTO.h"

struct Snapshot {

    std::vector<BuildingDTO*> buildings;
    std::vector<UnitDTO*> units;
    std::vector<PlayerDTO*> players;


    Snapshot(std::vector<BuildingDTO*> &buildings, std::vector<UnitDTO*> &units, std::vector<PlayerDTO*> &players):
        buildings(std::move(buildings)),
        units(std::move(units)),
        players(std::move(players)) {}


    Snapshot(Snapshot &&other) noexcept :
    buildings(std::move(other.buildings)),
    units(std::move(other.units)),
    players(std::move(other.players)) {}


    PlayerDTO getPlayer(InstanceId player_id1) {
        PlayerDTO player_ret(0,0,0);
        for (auto* player : players) {
            if (player->player_id == player_id1) {
                return *player;
            }
        }
        return player_ret;
    }


    Snapshot(Snapshot &copy) = delete;
    Snapshot& operator=(Snapshot &copy) = delete;
    Snapshot& operator=(Snapshot &&other) = delete;
};


#endif //DUNE_BUILDINGDTO_H