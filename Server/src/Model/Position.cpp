#include "../../includes/Model/Position.h"

Position::Position() : x(0), y(0) {}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}


bool Position::operator==(const Position &other) const {
    return other.x == this->x && other.y == this->y;
}

bool Position::operator<(const Position &other) const {
    if (this->x == other.x) {
        return this->y < other.y;
    } else {
        return this->x < other.x;
    }
}

int Position::sqrtDistance(const Position &pos) const {
    return (this->x - pos.x) * (this->x - pos.x) + (this->y - pos.y) * (this->y - pos.y);
}
