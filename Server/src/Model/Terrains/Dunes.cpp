#include "../../../includes/Model/Terrains/Dunes.h"

Dunes::Dunes() : Terrain(DUNE_KEY) {
    speed_factor = 2;
}

void Dunes::buildOn(Building *building) {

}