//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONUNITCL_H
#define DUNE_BUTTONUNITCL_H


#include "../../../Object/GameObject.h"

class ButtonUnitCL : public GameObject{
protected:
    int m_id;
    char m_player;
    int m_constructionTime;
    bool m_selectStatus;
    bool m_ready;

public:
    ButtonUnitCL(char textureID, SDL2pp::Point position, int id, char player, int constructionTime, bool selectStatus, bool ready);

    void update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

    virtual ~ButtonUnitCL() {}
};


#endif //DUNE_BUTTONUNITCL_H
