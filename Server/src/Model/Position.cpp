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

void Position::setX(int x1) {
    this->x = x1;
}

void Position::setY(int y1) {
    this->y = y1;
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


bool Position::operator!=(const Position& otra) const {
    return (this->x != otra.x || this->y != otra.y);
}

Position Position::operator+(const Position& otra) const {
    return Position(this->x + otra.x, this->y + otra.y);
}

Position::Position(const Position& otra) {
    this->x = otra.x;
    this->y = otra.y;
}

Position& Position::operator=(const Position& other) {
    if (this == &other)
        return *this;
    this->x = other.x;
    this->y = other.y;
    return *this;
}

int Position::sqrtDistance(const Position &pos) const {
    return (this->x - pos.x) * (this->x - pos.x) + (this->y - pos.y) * (this->y - pos.y);
}