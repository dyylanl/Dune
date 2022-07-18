//
// Created by riclui on 15/07/22.
//

#ifndef DUNE_INFOPLAYER_H
#define DUNE_INFOPLAYER_H


#include "../Object/GameObject.h"

class InfoPlayer : public GameObject{
private:
    int m_gold;
    int m_energy;
public:
    InfoPlayer(int gold, int energy);

    void processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera,
                      SoundManager &soundManager);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~InfoPlayer() {}
};


#endif //DUNE_INFOPLAYER_H
