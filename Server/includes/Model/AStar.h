#ifndef __ASTAR_H__
#define __ASTAR_H__

#include "AStarNode.h"
#include "Unit/Unit.h"
#include "Map.h"

#include <set>
#include <map>
#include <stack>
#include <vector>

class AStar {
private:
    std::vector<AStarNode> closeList;
    std::vector<AStarNode> openList;
    Map& map;

public:
    explicit AStar(Map &map);

    static std::stack<Position> reconstructPath(const std::map<Position, Position> &best_path, const Position &start);

    std::stack<Position> makePath(Unit &unit, Position end);
};

#endif	// __ASTAR_H__
