#ifndef __TERRAIN_H__
#define __TERRAIN_H__

class Terrain {
protected:
    char key;
    bool occupied;
    int speed_factor;
public:
    Terrain();
    explicit Terrain(char key);
    void occupy();
    bool isOccupied();
    int getSpeedFactor();
    bool operator==(const Terrain& terrain);
    virtual char getKey();
};

#endif	// __TERRAIN_H__
