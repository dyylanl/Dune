#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <vector>
#include "../Attackable.h"

class Building : public Attackable {
public:
    enum BuildingType {
        BARRACKS,
        CONSTRUCTION_YARD,
        HEAVY_FACTORY,
        LIGHT_FACTORY,
        SPICE_REFINERY,
        SPICE_SILO,
        WIND_TRAP
    };

    Building(const int x, const int y, int blockWidth, int blockHeight, const int energy, const int cost,
             const int hitPoints, const int width,
             const int height, BuildingType type);
    virtual ~Building();
    bool operator==(const Building& other);
    virtual void reciveBonusDammage(const Weapon &weapon) override;
    virtual int getCapacity();
    bool is(BuildingType type);
    Position& getClosestPosition(Position& position) override;

    int getId() {return id;}
    void demolish();

    //static BuildingType getBuildingType(char type);

    const int id;
    const int width, height;
    const int energy;
    const int cost;
    BuildingType key;

private:
    static int counter;
    std::vector<Position> all_positions;
};

#endif //__BUILDING_H__
