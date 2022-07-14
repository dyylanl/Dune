//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_VEHICLE_H
#define DUNE_VEHICLE_H


#include "../Object/GameObject.h"
#include <math.h>

class Vehicle : public GameObject{
protected:
    int m_id;
    int m_player;
    bool m_selectStatus;
    SDL2pp::Point m_posAction;
    int m_life;
    bool m_action;

public:
    Vehicle(char textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life, bool action);

    void processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) = 0;

    virtual ~Vehicle() {}
};


#endif //DUNE_VEHICLE_H
