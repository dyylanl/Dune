#ifndef __UNIT_H__
#define __UNIT_H__

#include <stack>
#include "../Weapons/Rocket.h"
#include "../Objects/Attackable.h"

class Terrain;
class Player;

class Unit : public Attackable {
    private:
    char type;
public:

    const int unit_id;
    int player_id;

    enum UnitType {
        LIGHT_INFANTRY,
        FREMEN,
        HEAVY_INFANTRY,
        SARDAUKAR,
        TRIKE,
        SONIC_TANK,
        RAIDER,
        DEVIATOR,
        TANK,
        DEVASTATOR,
        HARVESTER
    };

    Unit(char type, const int x, const int y, const int hitPoints, const int speed, const int cost, int player_id);
    virtual ~Unit();
    bool operator==(const Unit& other);
    void setPath(std::stack<Position> path, Position destiny);
    void move(Map &map);
    virtual void actionOnPosition(Map& map, Position& pos);
    Player& getPlayer();
    virtual void makeAttack(Map &map);
    virtual bool shotARocket();
    virtual Rocket* getRocket();
    virtual bool canMoveAboveTerrain(Terrain &terrain);
    char getType() {return type;}
    void select();
    bool isSelected() {return selected;}
    bool isAttacking() {return attacking;}
    Position getPosition() {return pos;}
    Position getNextPosition() {return next_pos;}
    int getCost() {return cost;}
    void kill() {life = 0;}

    virtual void attack(Attackable* enemy) = 0;

protected:
    Position pos;
    static int counter;
    const int speed;
    const int cost;
    int actual_speed;
    std::stack<Position> pathToDestiny;
    Position destiny;
    Position next_pos;
    Player* player;
    bool selected;
    bool attacking;
};

#endif //__UNIT_H__
