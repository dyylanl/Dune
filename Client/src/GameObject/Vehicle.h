//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_VEHICLE_H
#define DUNE_VEHICLE_H


#include "../Object/GameObject.h"

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

    void update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;
};


#endif //DUNE_VEHICLE_H
