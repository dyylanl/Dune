//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONREFINERY_H
#define DUNE_BUTTONREFINERY_H


#include "../../Graphics/TextureManager.h"
#include "../Button.h"

class ButtonRefinery : public Button {
public:
    ButtonRefinery(SDL2pp::Point position, SDL2pp::Point size);

    SDL2pp::Rect getShape();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_BUTTONREFINERY_H
