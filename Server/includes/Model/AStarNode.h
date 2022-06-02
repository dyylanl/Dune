#ifndef __ASTARNODE_H__
#define __ASTARNODE_H__

#include <vector>
#include "Position.h"
#include "Map.h"

struct AStarNode {
    AStarNode();
    explicit AStarNode(Position pos);
    std::vector<AStarNode> getAdjacents(Map &map) const;
    bool operator==(const AStarNode& other) const;
    int f, g, h;
    Position pos;
};

#endif //__ASTARNODE_H__
