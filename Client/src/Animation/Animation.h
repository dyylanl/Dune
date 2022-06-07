//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_ANIMATION_H
#define DUNE_ANIMATION_H

#include "SDL2pp/SDL2pp.hh"
#include "../Graphics/TextureManager.h"

#define FRAME_RATE 1000000.0f/25.0f

class SdlTexture;
class Area;


class Animation {
public:
    Animation(TextureManager &manager, std::string &textureID, SDL_RendererFlip flip);
    ~Animation();
    void update(float dt);
    void draw(SDL2pp::Renderer &renderer, SDL2pp::Point position, SDL2pp::Point spritSize);
    void setFlip(SDL_RendererFlip &flip);

private:
    void advanceFrame();
    /** SDL texture of the raw image. */
    //SDL2pp::Texture &texture;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Time elapsed since last update. */
    float elapsed;
    const std::string m_textureID;
    SDL_RendererFlip m_flip;
    TextureManager &m_TextureManager;
};


#endif //DUNE_ANIMATION_H
