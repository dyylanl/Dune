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
    m_Animation.update(dt);
}

void Player::draw(SDL2pp::Renderer &renderer) {
    m_Animation.draw(renderer, SDL2pp::Rect(x, y, 100, 100));
}

Player::Player(std::string textureID, TextureManager &manager, int posX, int posY)
: m_Animation(manager, textureID, SDL_FLIP_NONE), x(posX), y(posY), m_TextureID(textureID){}

