//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_GAMEOBJECT_H
#define DUNE_GAMEOBJECT_H

#include "SDL2pp/SDL2pp.hh"
#include "IObject.h"
#include "../../includes/Client.h"
#include <string>

/*enum TextureType: char {TRIKE, SONIC_TANK, RAIDER, DESVIATOR, TANK, DEVASTATOR, HARVESTER,
    LIGHT_INFANTRY, HEAVY_INFANTRY, FREMEN, SARDAUKAR,
    CONSTRUCTION_YARD, LIGHT_FACTORY, HEAVY_FACTORY,WIND_TRAP, REFINERY, SILO, BARRACK, PALACE,
    BTRIKE, BSONIC_TANK, BRAIDER, BDESVIATOR, BTANK, BDEVASTATOR, BHARVESTER,
    BLIGHT_INFANTRY, BHEAVY_INFANTRY, BFREMEN, BSARDAUKAR,
    BCONSTRUCTION_YARD, BLIGHT_FACTORY, BHEAVY_FACTORY, BWIND_TRAP, BREFINERY, BSILO, BBARRACK, BPALACE,
    MENU, ARENA, CIMA, DUNA, PRECIPICIO, ROCA};*/

class GameObject : public IObject{
protected:
    char m_textureID;
    SDL2pp::Point m_position;
    SDL2pp::Point m_size;

public:
    GameObject(char textureID, SDL2pp::Point position, SDL2pp::Point size)
    : m_textureID(textureID), m_position(position), m_size(size) {}

    virtual void update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue) = 0;

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

    virtual ~GameObject() {}

};


#endif //DUNE_GAMEOBJECT_H
