#include "../../../includes/Model/Units/Harvester.h"

Harvester::Harvester(int x, int y, int player_id) :
	Unit(HARVESTER_KEY,x, y,
	     GameConfiguration::getConfig().harvesterHitPoints,
	     GameConfiguration::getConfig().harvesterSpeed,
	     GameConfiguration::getConfig().harvesterCost, 
         player_id),

	spiceCapacity(GameConfiguration::getConfig().harvesterSpiceCapacity),
	spiceCollected(0),
	refinery(nullptr),
	farm_speed(GameConfiguration::getConfig().harvesterFarmSpeed),
	actual_farm_speed(0),
	load_speed(GameConfiguration::getConfig().harvesterLoadSpeed),
	actual_load_speed(0) 
    {}

Harvester::~Harvester() {}

bool Harvester::canMoveAboveTerrain(Terrain &terrain) {
	return terrain == Sand() || terrain == Dunes() || terrain == Rocks();
}

void Harvester::reciveBonusDammage(const Weapon &weapon) {
	life -= weapon.getVehicleBonus();
}

void Harvester::actionOnPosition(Map &map, Position &pos) {
	map.setDestiny(*this, pos.x, pos.y);
	farming_position = pos;
}


#include <iostream>
void Harvester::makeFarming(Map &map) {
	if (actual_farm_speed++ < farm_speed) {
		std::cout << "cosechando" << std::endl;
	} else {
		actual_farm_speed = 0;
	}

	if (!this->isFull()) {
		

		Position new_pos = map.getClosestSpeciaPosition(this->pos, 5);
		if (!(new_pos == this->pos)) {
			farming_position = new_pos;
			map.setDestiny(*this, new_pos.x, new_pos.y);
			std::cout << "lugar sin especia buscando otro" << std::endl;
		}
	}

	if (this->refinery == nullptr) {
		this->refinery = (Refinery*) player->getClosestBuilding(this->pos, Building::REFINERY);
		if (this->refinery == nullptr) {
			std::cout << "cosechadora parada pq no encuentra refineria" << std::endl;
		}
	}
	map.free(*refinery);
	map.setDestiny(*this, refinery->getPosition().x, refinery->getPosition().y);
	map.occupy(refinery);
	std::cout << "volviendo a descargar" << std::endl;
}

void Harvester::makeLoading(Map &map) {
	if (actual_load_speed++ < load_speed) {
		std::cout << "cargando cosechadora" << std::endl;
	} else {
		actual_load_speed = 0;
	}
	if (spiceCollected != 0) {
		if (refinery->load(*player)) {
			spiceCollected -= 1;
			std::cout << "cargando cosechadora" << std::endl;
		} else {
			std::cout << "cosechadora parada" << std::endl;
		}
	} else {
		map.setDestiny(*this, farming_position.x, farming_position.y);
		std::cout << "yendo a buscar especia" << std::endl;
	}
}
/*
UnitState* Harvester::makeBacking(Map &map) {
	if (this->move(map)) {
		return (UnitState *) &Unit::backing;
	} else {
		if (spiceCollected == 0) {
			return (UnitState*)&Unit::stopped;
		} else {
			return (UnitState*)&Unit::loading;
		}
	}
}*/

void Harvester::farm(Map &map) {
    std::cout << "intentando cosechar" << std::endl;
	int farm = map.at(farming_position).farm();
	if (farm != 0) {
        if (!isFull()) {
            spiceCollected += farm;
		    map.updateSpice(farming_position.x, farming_position.y);
            std::cout << "se encontro especia" << std::endl;
        } else {
            std::cout << "se encontro especia pero la cosechadora esta llena" << std::endl;
            map.free(*refinery);
	        map.setDestiny(*this, refinery->getPosition().x, refinery->getPosition().y);
	        map.occupy(refinery);
	        std::cout << "volviendo a la refineria" << std::endl;
        }
	} else { // no se encontro especia en la posicion actual => la muevo a otra que tal vez alla
        Position new_pos = map.getClosestSpeciaPosition(this->pos, 5);
		if (!(new_pos == this->pos)) {
			farming_position = new_pos;
			map.setDestiny(*this, new_pos.x, new_pos.y);
			std::cout << "lugar sin especia buscando otro" << std::endl;
		}
	}
}

bool Harvester::isFull() {
	return spiceCollected >= spiceCapacity;
}

void Harvester::move(Map &map) {
    farm(map);
    Unit::move(map);
}

void Harvester::attack(Attackable* enemy) {
    return;
}