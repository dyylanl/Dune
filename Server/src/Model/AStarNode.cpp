#include "../../includes/Model/AStarNode.h"

std::vector<AStarNode> AStarNode::getAdjacents(Map &map) const {
    std::vector<AStarNode> adjacents;
    for (int i = -1 ; i <= 1 ; ++i) {
        for (int j = -1 ; j <= 1 ; ++j) {
            Position position(pos.getX() + i, pos.getY() + j);
            if ((i != 0 || j != 0) && map.isValid(position)) {
                adjacents.emplace_back(position);
            }
        }
    }
    return adjacents;
}

AStarNode::AStarNode(Position pos) : f(0), g(0), h(0), pos(pos) {
    //this->pos.normalizeToBlock();
}

bool AStarNode::operator==(const AStarNode &other) const {
    return other.pos == this->pos;
}

AStarNode::AStarNode() :
        f(0),
        g(0),
        h(0),
        pos(0, 0) {}
