//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTON_H
#define DUNE_BUTTON_H

#include "SDL2pp/SDL2pp.hh"
#include "../Graphics/TextureManager.h"
#include "../Object/GameObject.h"


class Button : public GameObject{
public:
    Button(std::string textureID, SDL2pp::Point position, SDL2pp::Point size) : GameObject(textureID, position, size){}
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;
    virtual SDL2pp::Rect getShape() = 0;
};


#endif //DUNE_BUTTON_H