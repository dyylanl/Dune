//
// Created by riclui on 28/05/22.
//

#include "Animation.h"

#include "SDL2pp/SDL2pp.hh"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

Animation::~Animation() {}

void Animation::update(float dt) {
    this->elapsed += dt;
    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */

void Animation::advanceFrame() {
    this->currentFrame += 1;
    this->currentFrame = this->currentFrame % this->numFrames;
}

void Animation::setFlip(SDL_RendererFlip &flip) {
    m_flip = flip;
}

/*void Animation::draw(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest) {
    // orig: selecionamos el frame
    m_TextureManager.draw(renderer, m_textureID, SDL2pp::Rect(1 , 1, this->size, this->size),
                          dest,
                          0.0,                // don't rotate
                          m_flip );
}*/

void Animation::draw(SDL2pp::Renderer &renderer, SDL2pp::Point position, SDL2pp::Point spritSize) {
    m_TextureManager.draw(renderer, m_textureID, position.GetX(), position.GetY(), spritSize, m_flip);
}

Animation::Animation(TextureManager &manager, std::string &textureID, SDL_RendererFlip flip) : currentFrame(0),
                                                                                              numFrames(8),
                                                                                              size(64), elapsed(0.0f), m_textureID(textureID), m_flip(flip), m_TextureManager(manager){}


