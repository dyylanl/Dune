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
    }
}

void Player::draw(SDL2pp::Renderer &renderer) {
    //m_Animation.draw(renderer, SDL2pp::Rect(corner, SDL2pp::Point(100, 100)));
    //SDL2pp::Point size(100, 100);
    m_Animation.draw(renderer, corner, size);
}

SDL2pp::Rect Player::getShape() {
    return SDL2pp::Rect(corner, SDL2pp::Point(100, 100));
}

void Player::select() {
    selectStatus = true;
}

