//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_UNITNEW_H
#define DUNE_UNITNEW_H


#include "../Object/GameObject.h"

class UnitNew : public GameObject{
protected:
    int m_id;
    int m_player;
    bool m_selectStatus;
    SDL2pp::Point m_posAction;
    int m_life;
    bool m_action;

public:
    UnitNew(std::string textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life, bool action)
    : GameObject(textureID, position, size) ,m_id(id), m_player(player), m_selectStatus(selecStatus), m_posAction(posAction), m_life(life),  m_action(action) {}
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;
    virtual SDL2pp::Rect getShape() = 0;
};


#endif //DUNE_UNITNEW_H
