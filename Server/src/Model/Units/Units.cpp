#include <iostream>
#include "../../../includes/Model/Units/Unit.h"
#include "../../../config/GameConfiguration.h"
#include "../../../includes/Model/Map.h"

int Unit::counter = 0;
Unit::Unit(char type1, const int x, const int y, const int hitPoints, const int speed, const int cost, int player_id1) :
        Attackable(hitPoints, x, y),
        type(type1),
        unit_id(counter),
        player_id(player_id1),
        pos(x,y),
        speed(speed),
        cost(cost),
        actual_speed(0),
        pathToDestiny(),
        destiny(x, y),
        next_pos(x, y),
        selected(false),
        attacking(false) {
    counter += 1;
}


Unit::~Unit() {}


void Unit::move(Map &map) {
    map.at(pos).occupy();

    // Manejo la velocidad sobre el terreno
    int terrain_factor = map.getSpeedFactorAt(pos);
    int counter_limit = terrain_factor * GameConfiguration::getConfig().speedFactor;
    int speed_counter = actual_speed;
    actual_speed += speed;

    // Actualizo la nueva pos y me fijo si hay q recalcular el camino
    if (!pathToDestiny.empty()) {
        next_pos = pathToDestiny.top();
        pathToDestiny.pop();
        if (map.at(next_pos).isOccupied()) { // me fijo si el mapa fue modificado
            map.setDestiny(*this, destiny.getX(), destiny.getY()); // si fue modificado recalculo A*
            return; // como fue modificado ahora no me muevo
        } else {
            if (speed_counter >= counter_limit) {
                if (!(pos == next_pos)) { // si la pos actual es distinta a la sig me muevo
                    map.at(pos).free(); // entonces libero su posicion actual
                    int block_movement = GameConfiguration::getConfig().blockMovement;  // config de movimiento en el yaml
                    pos.x += (next_pos.x < pos.x) ? -block_movement : ((next_pos.x > pos.x) ? +block_movement : 0); // deltas
                    pos.y += (next_pos.y < pos.y) ? -block_movement : ((next_pos.y > pos.y) ? +block_movement : 0);
                    map.at(pos).occupy(); // ocupo la nueva posicion de la unidad
                    if (!pathToDestiny.empty()) {
                        next_pos = pathToDestiny.top();
                    }
                }
                actual_speed = speed_counter - counter_limit;
            }
        }
    }
    attacking = false;
    if (map.getClosestAttackable(pos,1,player_id) != nullptr) {
        attacking = true;
        attack(map.getClosestAttackable(pos,1,player_id));
    }
}

void Unit::setPath(std::stack<Position> path, Position destiny1) {
    pathToDestiny = path;
    this->destiny = destiny1;
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

bool Unit::operator==(const Unit &other) {
    return this->unit_id == other.unit_id;
}

bool Unit::canMoveAboveTerrain(Terrain &terrain) {
    return true;
}

void Unit::makeAttack(Map &map) {
    return;
}

void Unit::select() {
    if (selected) { // si esta seleccionada y la vuelve a seleccionar => deselecciono
        selected = false;
    } else {
        this->selected = true;
    }
}
