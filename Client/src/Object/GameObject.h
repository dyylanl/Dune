//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_GAMEOBJECT_H
#define DUNE_GAMEOBJECT_H

#include "SDL2pp/SDL2pp.hh"
#include "IObject.h"
#include <string>

class GameObject : public IObject{
protected:
    std::string m_textureID;
    SDL2pp::Point m_position;
    SDL2pp::Point m_size;

public:
    GameObject(std::string textureID, SDL2pp::Point position, SDL2pp::Point size)
    : m_textureID(textureID), m_position(position), m_size(size) {}
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;
    virtual SDL2pp::Rect getShape() = 0;
};


#endif //DUNE_GAMEOBJECT_H
