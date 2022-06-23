//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTON_H
#define DUNE_BUTTON_H

#include "SDL2pp/SDL2pp.hh"
#include "../Graphics/TextureManager.h"
#include "../Object/GameObject.h"


class Button : public GameObject{
protected:
    int m_id;
    char m_player;
    int m_constructionTime;

public:
    Button(std::string textureID, SDL2pp::Point position, int id, char player, int constructionTime) : GameObject(textureID, position, SDL2pp::Point(66, 66)){}

    void update(EventManager &eventManager, BlockingQueue<Action *> &queue);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

};


#endif //DUNE_BUTTON_H
