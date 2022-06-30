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

    explicit AStar(Map& map);
    /*
    *   Con la nueva implementacion de pasar el stack este metodo no sirve pa na
    */
    static std::stack<Position> reconstructPath(std::map<Position, Position> &best_path, Position &start);
    /*
    *   Este metodo tendria que recibir por parametro un stack de posiciones y el algoritmo de busqueda
    *   ir pusheando a ese stack, asi a medida que se pushea una posicion el engine la puede popear y enviar.
    */
    std::stack<Position> makePath(Position start, Position end, std::vector<Position*>& path);
};

#endif	// __ASTAR_H__
