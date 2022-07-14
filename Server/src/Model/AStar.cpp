#include <map>
#include <stack>
#include <algorithm>
#include <vector>
#include <iostream>
#include "../../includes/Model/AStar.h"


AStar::AStar(Map &map) : map(map) {}

std::stack<Position> AStar::reconstructPath(const std::map<Position, Position> &best_path, const Position &start) {
    std::stack<Position> total_path;
    Position current(start);
    total_path.push(current);
    while (best_path.find(current) != best_path.end()) {
        current = best_path.at(current);
        total_path.push(current);
    }
    total_path.pop();
    return (total_path);
}

std::stack<Position> AStar::makePath(Unit &unit, Position end) {
    std::map<Position, Position> best_path;
    AStarNode n_end(end);
    AStarNode n_start(unit.getPosition());
    openList.push_back(n_start);
    while (!openList.empty()) {
        auto curr_node_itr = openList.begin();
        for (auto itr = openList.begin(); itr != openList.end() ; itr++) {
            if (itr->f < curr_node_itr->f) {
                curr_node_itr = itr;
            }
        }
        if (*curr_node_itr == n_end) {
            return this->reconstructPath(best_path, end);
        }
        closeList.push_back(AStarNode(*curr_node_itr));
        openList.erase(curr_node_itr);
        curr_node_itr = closeList.end() - 1;
        std::vector<AStarNode> children = curr_node_itr->getAdjacents(this->map);
        for (AStarNode& child : children) {
            auto child_cl_itr = std::find(closeList.begin(), closeList.end(), child);
            if (child_cl_itr != closeList.end() || !map.canMove(unit, child.pos)) {
                continue;
            }
            child.g = curr_node_itr->g + 1;
            child.h = child.pos.sqrtDistance(n_end.pos);
            child.f = child.g + child.h;
            auto child_ol_itr = std::find(openList.begin(), openList.end(), child);
            if (child_ol_itr == openList.end()) {
                openList.push_back(child);
            } else {
                if (child.g >= child_ol_itr->g) {
                    continue;
                }
                child_ol_itr->g = child.g;
                child_ol_itr->f = child.f;
            }
            best_path[child.pos] = curr_node_itr->pos;
        }
    }
    return (std::stack<Position>());
}