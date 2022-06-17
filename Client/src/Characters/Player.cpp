//
// Created by riclui on 28/05/22.
//

#include "Player.h"

Player::Player(std::string textureID, TextureManager &manager, SDL2pp::Point position, SDL2pp::Point size)
        : m_Animation(manager, textureID, SDL_FLIP_NONE), corner(position), size(size) ,m_TextureID(textureID), selectStatus(false){}

Player::~Player() {}

void Player::update(EventManager &eventManager, float dt) {
    //m_Animation.update(dt);
    if(selectStatus && eventManager.mouseButtonDown(RIGHT)){
        corner = eventManager.getMouse();
        selectStatus = false;
    }
}

void Player::draw(SDL2pp::Renderer &renderer) {
    m_Animation.draw(renderer, corner, size);
}

SDL2pp::Rect Player::getShape() {
    return SDL2pp::Rect(corner, size);
}

void Player::select() {
    selectStatus = true;
}
