//
// Created by riclui on 28/05/22.
//

#include "Player.h"

Player::~Player() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void Player::update(float dt) {
    if (moving) {
        m_Animation.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Player::draw(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    m_Animation.setFlip(flip);
    m_Animation.draw(renderer, SDL2pp::Rect(x, y, 200, 200));
}

void Player::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Player::stopMoving() {
    moving = false;
}

Player::Player(std::string textureID, TextureManager &manager) : m_Animation(manager, textureID, SDL_FLIP_NONE),
facingLeft(false), moving(false), x(300), y(300), m_TextureID(textureID){}

