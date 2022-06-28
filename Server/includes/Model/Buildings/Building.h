#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <vector>
#include "../../../config/GameConfig.h"
#include "../Position.h"
#include "../Weapons/Weapon.h"
#include "../Units/Attackable.h"

//class Player;

class Building : public Attackable {
public:
    enum BuildingType {
        BARRACKS,
        CONSTRUCTION_CENTER,
        HEAVY_FACTORY,
        LIGHT_FACTORY,
        REFINERY,
        SILO,
        WIND_TRAP
    };

    Building(const int x, const int y, int blockWidth, int blockHeight, const int energy, const int cost,
             const int hitPoints, const int width,
             const int height, BuildingType type);

    //static Building getBuildType(char type, int pos_x, int pos_y);
    virtual ~Building();
    bool operator==(const Building& other);
    //virtual void reciveBonusDammage(const Weapon &weapon) override;
    virtual int getCapacity();
    bool is(BuildingType type);
    //void setPlayer(Player* player);
    //Player* getPlayer();
    //Position& getClosestPosition(Position& position) override;
    void demolish();
    bool hasNews();

    const int id;
    const int width, height;
    const int energy;
    const int cost;
private:
    static int counter;
    //Player* player;
    Position pos;
    BuildingType key;
    std::vector<Position> all_positions;

protected:
    bool news;
};

#endif //__BUILDING_H__
