//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_GAMEOBJECT_H
#define DUNE_GAMEOBJECT_H

#include "SDL2pp/SDL2pp.hh"
#include "IObject.h"
#include "../../includes/Client.h"
#include <string>

class GameObject : public IObject{
protected:
    char m_textureID;
    SDL2pp::Point m_position;
    SDL2pp::Point m_size;

public:
    GameObject(char textureID, SDL2pp::Point position, SDL2pp::Point size)
    : m_textureID(textureID), m_position(position), m_size(size) {}

    virtual void processEvent(SDL_Event &eventManager, BQueue<std::unique_ptr<CommandCL>> &queue) = 0;

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

    virtual ~GameObject() {}

};


#endif //DUNE_GAMEOBJECT_H
