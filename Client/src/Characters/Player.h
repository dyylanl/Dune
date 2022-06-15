//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_PLAYER_H
#define DUNE_PLAYER_H


#include "SDL2pp/SDL2pp.hh"
#include "../Animation/Animation.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventManager.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include <arpa/inet.h>

class Player {
private:
    Animation m_Animation;
    SDL2pp::Point corner;
    SDL2pp::Point size;
    std::string m_TextureID;
    bool selectStatus;

public:
    Player(std::string textureID, TextureManager &manager, SDL2pp::Point position, SDL2pp::Point size);
    ~Player();
    void update(EventManager &eventManager, float dt);
    void draw(SDL2pp::Renderer &renderer);
    SDL2pp::Rect getShape();

    void select();
};

#endif //DUNE_PLAYER_H
