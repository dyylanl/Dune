//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_IOBJECT_H
#define DUNE_IOBJECT_H


#include "../Graphics/TextureManager.h"
#include "../Action/CommandCL.h"
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/src/Queue/BQueue.h"
#include "../Sounds/SoundManager.h"

class IObject {
public:
    virtual void processEvent(SDL_Event &eventManager, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera,
                              SoundManager &soundManager) = 0;

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) = 0;

    virtual ~IObject() {}

};


#endif //DUNE_IOBJECT_H
