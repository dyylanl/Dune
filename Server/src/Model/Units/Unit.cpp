#include <iostream>
#include <stack>
#include "../../../includes/Model/Units/Unit.h"
#include "../../../includes/Model/Map.h"

int Unit::counter = 0;

Unit::Unit(const int x, const int y, const int hitPoints, const int speed, const int cost) :
        Attackable(hitPoints, x, y),
        id(counter),
        speed(speed),
        cost(cost),
        actual_speed(0),
        pathToDestiny(),
        foll_unit(nullptr),
        destiny(x, y),
        prev_foll_unit_pos(),
        next_pos(x, y),
        news(true) {
    counter += 1;
}

Unit::~Unit() {}

bool Unit::move(Map &map) {
    bool moved = true;
    int terrain_factor = 1;
    int counter_limit = terrain_factor * GameConfiguration::getConfig().speedFactor;
    int speed_counter = actual_speed;
    actual_speed += speed;
    if (speed_counter >= counter_limit) {
        if (pos == next_pos && !pathToDestiny.empty()) {
            next_pos = pathToDestiny.top();
            if ( map.at(next_pos).isOccupied() ) {
                std::cout << "Moviendo unidad" << std::endl;
            } else {
                pathToDestiny.pop();
            }
        }

        if (!(pos == next_pos)) {
            int block_movement = GameConfiguration::getConfig().blockMovement;
            pos.x += (next_pos.x < pos.x) ? -block_movement : ((next_pos.x > pos.x) ? +block_movement : 0);
            pos.y += (next_pos.y < pos.y) ? -block_movement : ((next_pos.y > pos.y) ? +block_movement : 0);
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

void Unit::follow(Attackable* other, Map& map) {
    foll_unit = other;
    prev_foll_unit_pos = foll_unit->getClosestPosition(pos);
    bool occupied_pos = map.at(prev_foll_unit_pos).isOccupied();
    if (occupied_pos)
        map.at(prev_foll_unit_pos).free();
    std::cout << "Seteando destino" << std::endl;
    if (occupied_pos)
        map.at(prev_foll_unit_pos).occupy();
}

void Unit::setPlayer(Player &player1) {
    this->player = &player1;
    this->player->subGold(this->cost);
}

Player& Unit::getPlayer() {
    return *player;
}


//todo terminar estados
bool Unit::isAttacking() {
    return false;
}


void Unit::checkForDeadVictim() {
    if (foll_unit != nullptr) {
        if (Unit::isDead(foll_unit)) {
            this->foll_unit = nullptr;
        }
    }
}

bool Unit::hasNews() {
    return (news);
}

bool Unit::operator==(const Unit &other) {
    return this->id == other.id;
}
