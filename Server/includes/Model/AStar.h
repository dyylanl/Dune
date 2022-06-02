#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <set>
#include <map>
#include <stack>
#include <algorithm>
#include <vector>
#include "AStarNode.h"
#include "Map.h"



class AStar {
private:
    std::vector<AStarNode> closeList;
    std::vector<AStarNode> openList;
    Map& map;

public:
    explicit AStar(Map &map);
    static std::stack<Position> reconstructPath(std::map<Position, Position> &best_path, Position &start);
    std::stack<Position> makePath(Unit &unit, Position end);
};

#endif	// __ASTAR_H__
