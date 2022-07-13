#include <vector>
#include "../../includes/Model/AStarNode.h"

std::vector<AStarNode> AStarNode::getAdjacents(Map &map) {
    std::vector<AStarNode> vec;
    for (int i = -1 ; i <= 1 ; ++i) {
        for (int j = -1 ; j <= 1 ; ++j) {
            Position p(pos.getX() + i, pos.getY() + j);
            if ((i != 0 || j != 0) && map.isValid(p)) {
                vec.push_back(AStarNode(p));
            }
        }
    }
    return (vec);
}

AStarNode::AStarNode(Position pos) : f(0), g(0), h(0), pos(pos) {}

bool AStarNode::operator==(const AStarNode &other) const {
    return other.pos == this->pos;
}

AStarNode::AStarNode() :
        f(0),
        g(0),
        h(0),
        pos(0, 0) {}
