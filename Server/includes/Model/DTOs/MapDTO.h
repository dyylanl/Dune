//
// Created by dypa on 25/06/22.
//

#ifndef DUNE_MAPDTO_H
#define DUNE_MAPDTO_H

#include <string>
#include <vector>
#include "../../defs.h"

struct MapDTO {
    std::string path;
    Id map_id;
    int rows, cols;
    int max_players;
    std::vector<std::vector<char>> map;
};


#endif //DUNE_MAPDTO_H
