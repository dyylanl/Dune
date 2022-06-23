//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_BUTTONYARDCL_H
#define DUNE_BUTTONYARDCL_H


#include "../Button.h"

class ButtonYardCL : public Button {
public:
    ButtonYardCL(int id, char player, int constructionTime);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_BUTTONYARDCL_H
