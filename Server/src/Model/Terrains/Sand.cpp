#include "../../../includes/Model/Terrains/Sand.h"

Sand::Sand(int spice) : Terrain(SAND_KEY), availableFarm(spice) {}

Sand::Sand(): Terrain(SAND_KEY), availableFarm(0) {}

int Sand::farm() {
    if (availableFarm > 0) {
        availableFarm--;
        return 1;
    } else {
        return 0;
    }
}

int Sand::getSpice() {
    return availableFarm;
}

bool Sand::hasFarm() {
    return (availableFarm > 0);
}

char Sand::getKey() {
    if (availableFarm > 300) {
        return 'S';
    } else if (availableFarm > 0) {
        return 'M';
    } else {
        return key;
    }
}

void Sand::buildOn(Building* building) {}