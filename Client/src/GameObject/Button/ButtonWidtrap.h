//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONWIDTRAP_H
#define DUNE_BUTTONWIDTRAP_H


#include "SDL2pp/SDL2pp.hh"
#include "../../Graphics/TextureManager.h"
#include "../Button.h"

class ButtonWidtrap : public Button{
public:
    ButtonWidtrap(SDL2pp::Point position, SDL2pp::Point size);

    SDL2pp::Rect getShape() {
        return SDL2pp::Rect(m_position, m_size);
    }

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_BUTTONWIDTRAP_H
