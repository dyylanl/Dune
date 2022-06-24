//
// Created by riclui on 22/06/22.
//

#ifndef DUNE_BUILDCL_H
#define DUNE_BUILDCL_H


#include "../Object/GameObject.h"

class BuildCL : public GameObject{
protected:
    int m_id;
    int m_player;
    int m_life;

public:
    BuildCL(std::string textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, int life)
    : GameObject(textureID, position, size) ,m_id(id), m_player(player), m_life(life) {}

    void update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

};


#endif //DUNE_BUILDCL_H
