#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "../../../includes/Model/Buildings/Building.h"

class Terrain {
protected:
    char key;
    bool occupied;
    bool builtOn;
    int speed_factor;

public:
    /*
     * Constructor de terreno, recibe la clave que contendra
     */
    explicit Terrain(char key);
    /*
     *  Ocupa el terreno
     */
    void occupy();
    /*
     * Se construye sobre el terreno
     */
    virtual void buildOn(Building* building);
    /*
     * Libera el terreno
     */
    virtual void free();
    /*
     * retorna true si esta ocupado el terreno
     */
    bool isOccupied();
    /*
     * retorna true si se puede cosntruir sobre el terreno
     * por default el terreno retorna false
     */
    bool isBuiltOn();
    /*
     * retorna una unidad de especia
     */
    virtual int farm();
    /*
     * retorna especia si es que la tiene
     */
    virtual int getSpice();
    /*
     * Retorna true si se puede cosechar
     */
    virtual bool hasFarm();
    virtual Building* getBuilding();
    int getSpeedFactor();
    bool operator==(const Terrain& terrain);
    virtual char getKey();
};

#endif	// __TERRAIN_H__
