#include "../../../includes/Model/Units/Unit.h"
#include "../../../includes/Model/Map.h"
#include "../../../includes/Model/Player.h"

int Unit::counter = 0;
Unit::Unit(const int x, const int y, const int hitPoints, const int speed, const int cost) :
        Attackable(hitPoints, x, y),
        id(counter),
        speed(speed),
        cost(cost),
        actual_speed(0),
        //state((UnitState*) & Unit::stopped),
        pathToDestiny(),
        foll_unit(nullptr),
        destiny(x, y),
        prev_foll_unit_pos(),
        next_pos(x, y),
        news(true)
{
    counter += 1;
}

bool Unit::move(Map &map) {
    bool moved = true;
    int terrain_factor = map.getSpeedFactorAt(pos);
    int counter_limit = terrain_factor * GameConfiguration::getConfig().speedFactor;
    int speed_counter = actual_speed;
    actual_speed += speed;
    if (speed_counter >= counter_limit) {
        if (pos == next_pos && !pathToDestiny.empty()) {
            next_pos = pathToDestiny.top();
            if ( map.at(next_pos).isOccupied() ) {
                map.setDestiny(*this, destiny.x, destiny.y);
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
//        state = (UnitState*)&Unit::moving;
    } else {
        next_pos = pos;
//        state = (UnitState*)&Unit::stopped;
    }
}

//bool Unit::isDead(const Attackable *unit) {
//    if (!unit) {
//        return true;
//    }
//    return unit->getLife() <= 0;
//}

void Unit::follow(Attackable* other, Map& map) {
    foll_unit = other;
    prev_foll_unit_pos = foll_unit->getClosestPosition(pos);
    bool occupied_pos = map.at(prev_foll_unit_pos).isOccupied();
    // Se libera la posicion objetivo para que el algoritmo pueda calcular el camino.
    // Luego se vuelve a ocupar
    if (occupied_pos)
        map.at(prev_foll_unit_pos).free();
    map.setDestiny(*this, foll_unit->getClosestPosition(pos).x, foll_unit->getClosestPosition(pos).y);
    if (occupied_pos)
        map.at(prev_foll_unit_pos).occupy();
    //state = (UnitState*)&Unit::moving;
}

void Unit::setPlayer(Player &player1) {
    this->player = &player1;
    this->player->subGold(this->cost);
}

Player &Unit::getPlayer() {
    return *player;
}
/*
void Unit::makeAction(Map &map) {
    state = state->makeAction(map, *this);
}

bool Unit::isAttacking() {
    return state->isAttacking();
}

UnitState *Unit::makeFollow(Map &map) {
    return state;
}

UnitState *Unit::makeAttack(Map &map) {
    return state;
}

UnitState *Unit::makeStopped(Map &map) {
    return state;
}*/
/*
void Unit::actionOnPosition(Map &map, Position &pos) {
//    Unit* foll_unit = map.getClosestUnit(pos, 50 * 50, *player, false);
    Attackable* foll_unit = map.getClosestAttackable(pos, 50 * 50, *player);
    if (foll_unit != nullptr) {
        this->follow(foll_unit, map);
        state = (UnitState*) &Unit::following;
    } else {
        map.setDestiny(*this, pos.x, pos.y);
        state = (UnitState*) &Unit::moving;
    }
}
*/

bool Unit::shotARocket() {
    return false;
}

Rocket* Unit::getRocket() {
    return nullptr;
}

void Unit::checkForDeadVictim() {
    if (foll_unit != nullptr) {
        if (Unit::isDead(foll_unit)) {
            this->foll_unit = nullptr;
            //this->state = (UnitState*)&Unit::stopped;
        }
    }
}

bool Unit::hasNews() {
    return (news);
}

bool Unit::operator==(const Unit &other) {
    return this->id == other.id;
}
