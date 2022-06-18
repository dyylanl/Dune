//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_OBJECTGAME_H
#define DUNE_OBJECTGAME_H


#include "SDL2pp/SDL2pp.hh"
#include "../Animation/Animation.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventManager.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include "Object.h"
#include <arpa/inet.h>

class ObjectGame {
private:
    Object *m_ObjectType;
    Animation m_Animation;
    /*SDL2pp::Point corner;
    SDL2pp::Point size;
    std::string m_TextureID;
    bool selectStatus;*/

public:
    ObjectGame(std::string textureID, TextureManager &manager, SDL2pp::Point position, SDL2pp::Point size);
    ~ObjectGame();
    void update(EventManager &eventManager, float dt);
    void draw(SDL2pp::Renderer &renderer);
    SDL2pp::Rect getShape();
    void select();

    ObjectGame(Object *pUnidad, TextureManager &textureManager);
};

#endif //DUNE_OBJECTGAME_H
