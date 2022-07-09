#ifndef DUNE_SNAPSHOT_H
#define DUNE_SNAPSHOT_H

#include <vector>
#include "../../defs.h"
#include "BuildingDTO.h"
#include "UnitDTO.h"

struct Snapshot {
    std::vector<BuildingDTO*> buildings;
    std::vector<UnitDTO*> units;
    Snapshot(std::vector<BuildingDTO*> &buildings, std::vector<UnitDTO*> &units): 
        buildings(std::move(buildings)), units(std::move(units)) {}
    Snapshot(Snapshot &&other): buildings(std::move(other.buildings)), units(std::move(other.units)) {}
    Snapshot(Snapshot &copy) = delete;

    Snapshot& operator=(Snapshot &copy) = delete;
    Snapshot& operator=(Snapshot &&other) = delete;
};


#endif //DUNE_BUILDINGDTO_H