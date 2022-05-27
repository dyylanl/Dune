#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <stack>
#include <algorithm>
#include <vector>
#include <map>

#include "../../includes/Model/Position.h"
#include "../../includes/Model/Map.h"
#include "AStarNode.h"

class AStar {
private:
    // Guardamos las casillas que ya revisamos.
    std::vector<AStarNode> closeList;
    // Guardamos las casillas que pueden seguir abriendo camino.
    std::vector<AStarNode> openList;
    // Pasos que dimos hasta llegar al destino. (g)
    // int weight;
    // Distancia euclidiana entre el origien y el destino abs(Xf - Xi) + abs(Yf - Yi)
    // int heuristic; (h)
    // Suma de weight + heuristic; (f)
    //int f;
    Map& map;

public:
    explicit AStar(Map &map);
    static std::stack<Position> reconstructPath(const std::map<Position, Position> &best_path, const Position &start);
    std::stack<Position> makePath(Unit &unit, const Position& end);
};


#endif	// __ASTAR_H__
