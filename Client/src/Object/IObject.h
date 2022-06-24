//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_IOBJECT_H
#define DUNE_IOBJECT_H


#include "../Graphics/TextureManager.h"
#include "../Action/CommandCL.h"
#include "../../../Common/includes/BlockingQueue.h"

class IObject {
public:
    virtual void update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue) = 0;

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

};


#endif //DUNE_IOBJECT_H
