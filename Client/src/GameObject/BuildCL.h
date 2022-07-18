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
    BuildCL(char textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, int life);

    void processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera,
                      SoundManager &soundManager) {}

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) = 0;

    void setPosition(SDL2pp::Point position);

    virtual ~BuildCL() {}
};


#endif //DUNE_BUILDCL_H
