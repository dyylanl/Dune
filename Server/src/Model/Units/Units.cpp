#include <iostream>
#include "../../../includes/Model/Units/Unit.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Map.h"

int Unit::counter = 0;
Unit::Unit(char type1, const int x, const int y, const int hitPoints, const int speed, const int cost) :
        Attackable(hitPoints, x, y),
        type(type1),
        id(counter),
        pos(x,y),
        speed(speed),
        cost(cost),
        actual_speed(0),
        pathToDestiny(),
        foll_unit(nullptr),
        destiny(x, y),
        prev_foll_unit_pos(),
        next_pos(x, y),
        news(true),
        selected(false) {
    counter += 1;
}

Unit::~Unit() {}

bool Unit::move(Map &map) {
    bool moved = true;
    int terrain_factor = map.getSpeedFactorAt(pos);
    int counter_limit = terrain_factor * GameConfiguration::getConfig().speedFactor;
    int speed_counter = actual_speed;
    actual_speed += speed;
    /*while (!pathToDestiny.empty()) {
        next_pos = pathToDestiny.top();
        pathToDestiny.pop();
        this->setPosition(next_pos);
        std::cout << "Moviendo unidad a " << next_pos.getX() << "," << next_pos.getY() << std::endl;
    }
    return moved;*/
    if (speed_counter >= counter_limit) {
        if (pos == next_pos && !pathToDestiny.empty()) {
            next_pos = pathToDestiny.top();
            pathToDestiny.pop();
            if (map.at(next_pos).isOccupied()) { // me fijo si el mapa no fue modificado
                map.setDestiny(*this, destiny.x, destiny.y); // si fue modificado recalculo A*
            }
        }
        if (!(pos == next_pos)) {
            int block_movement = GameConfiguration::getConfig().blockMovement;
            pos.x += (next_pos.x < pos.x) ? -block_movement : ((next_pos.x > pos.x) ? +block_movement : 0);
            pos.y += (next_pos.y < pos.y) ? -block_movement : ((next_pos.y > pos.y) ? +block_movement : 0);
            std::cout << "[UNIT]: " << pos.x << "," << pos.y << std::endl;
            moved = true;
            this->news = true;
        } else {
            map.at(pos).occupy();
            moved = false;
        }
        actual_speed = speed_counter - counter_limit;
    }
    return moved;
}

void Unit::setPath(std::stack<Position> path, Position destiny1) {
    pathToDestiny = path;
    this->destiny = destiny1;
    if (!path.empty()) {
        next_pos = pathToDestiny.top();
        pathToDestiny.pop();
    } else {
        next_pos = pos;
    }
}

Player &Unit::getPlayer() {
    return *player;
}

void Unit::actionOnPosition(Map &map, Position &pos1) {
            map.setDestiny(*this, pos1.x, pos1.y);
}

bool Unit::shotARocket() {
    return false;
}

Rocket* Unit::getRocket() {
    return nullptr;
}

bool Unit::hasNews() {
    return (news);
}

bool Unit::operator==(const Unit &other) {
    return this->id == other.id;
}

bool Unit::canMoveAboveTerrain(Terrain &terrain) {
    return true;
}

void Unit::makeAttack(Map &map) {
    return;
}

void Unit::select() {
    this->selected = true;
}
