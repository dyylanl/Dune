//
// Created by riclui on 28/05/22.
//

#include "Animation.h"

#include <SDL2pp/SDL2pp.hh>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

/*Animation::Animation(SDL2pp::Texture &texture) : texture(texture), currentFrame(0),
                                                 numFrames(8),
                                                 size(50), elapsed(0.0f) {
    assert(this->numFrames > 0);
    assert(this->size > 0);
}*/

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
/*void Animation::draw(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType) {
    renderer.Copy(
            texture,
            SDL2pp::Rect(1 + (1 + this->size) * this->currentFrame, 0, this->size, this->size),
            dest,
            0.0,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );
}*/

void Animation::advanceFrame() {
    this->currentFrame += 1;
    this->currentFrame = this->currentFrame % this->numFrames;
}

/*Animation::Animation(SDL2pp::Texture &texture, const std::string textureID, SDL_RendererFlip flip) : texture(texture), currentFrame(0),
numFrames(this->texture.GetWidth() / this->texture.GetHeight()),
size(this->texture.GetHeight()), elapsed(0.0f), m_textureID(textureID), m_flip(flip){
    std::cout << "nro frames:" << numFrames << " size:" << size << std::endl;
}*/

void Animation::setFlip(SDL_RendererFlip &flip) {
    m_flip = flip;
}

void Animation::draw(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest) {
    /*renderer.Copy(
            texture,
            SDL2pp::Rect(1 + (1 + this->size) * this->currentFrame, 0, this->size, this->size),
            dest,
            0.0,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            m_flip
    );*/
    m_TextureManager.draw(renderer, m_textureID, SDL2pp::Rect(1 + (1 + this->size) * this->currentFrame, 0, this->size, this->size),
                          dest,
                          0.0,                // don't rotate
                          m_flip );
}

Animation::Animation(TextureManager &manager, std::string &textureID, SDL_RendererFlip flip) : currentFrame(0),
                                                                                              numFrames(8),
                                                                                              size(50), elapsed(0.0f), m_textureID(textureID), m_flip(flip), m_TextureManager(manager){}
