//
// Created by riclui on 28/05/22.
//

#include "Player.h"

Player::~Player() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void Player::update(EventManager &eventManager, float dt) {
    //m_Animation.update(dt);
    if(selectStatus && eventManager.MouseButtonDown(LEFT)){
        corner = eventManager.getMouse();
    }
}

void Player::draw(SDL2pp::Renderer &renderer) {
    m_Animation.draw(renderer, SDL2pp::Rect(corner, SDL2pp::Point(100, 100)));
}

Player::Player(std::string textureID, TextureManager &manager, SDL2pp::Point point)
: m_Animation(manager, textureID, SDL_FLIP_NONE), corner(point), m_TextureID(textureID), selectStatus(false){}

SDL2pp::Rect Player::getShape() {
    return SDL2pp::Rect(corner, SDL2pp::Point(100, 100));
}

void Player::select() {
    selectStatus = true;
}

