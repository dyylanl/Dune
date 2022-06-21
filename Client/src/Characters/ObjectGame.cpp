//
// Created by riclui on 28/05/22.
//

#include "ObjectGame.h"

/*ObjectGame::ObjectGame(std::string textureID, TextureManager &manager, SDL2pp::Point position, SDL2pp::Point size)
        : m_Animation(manager, textureID, SDL_FLIP_NONE), corner(position), size(size) ,m_TextureID(textureID), selectStatus(false){}*/

ObjectGame::~ObjectGame() {}

void ObjectGame::update(EventManager &eventManager, float dt) {
    //m_Animation.update(dt);
    /*if(selectStatus && eventManager.mouseButtonDown(RIGHT)){
        corner = eventManager.getMouse();
        selectStatus = false;
    }*/
}

void ObjectGame::draw(SDL2pp::Renderer &renderer) {
    //std::cout << m_ObjectType->getPosition() << "---" << m_ObjectType->getSize() << std::endl;
    m_Animation.draw(renderer, m_ObjectType->getPosition(), SDL2pp::Point(30, 30));
}

/*SDL2pp::Rect ObjectGame::getShape() {
    return SDL2pp::Rect(corner, size);
}

void ObjectGame::select() {
    selectStatus = true;
}*/

ObjectGame::ObjectGame(Object *pUnidad, TextureManager &textureManager) : m_ObjectType(pUnidad), m_Animation(textureManager, pUnidad->getUnitType()){

}
