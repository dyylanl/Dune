//
// Created by riclui on 30/05/22.
//

#include "TextureManager.h"

void TextureManager::load(std::string id, std::string filename) {
    m_TextureMap[id] = filename;
}

TextureManager::TextureManager(SDL2pp::Renderer &renderer) : m_renderer(renderer){
}

void TextureManager::draw(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point spritSize,
                          SDL_RendererFlip flip) {
    SDL2pp::Texture texture(m_renderer,
                            SDL2pp::Surface(m_TextureMap[id]).SetColorKey(true, 0));
    SDL2pp::Point posFrame(1,1);
    SDL2pp::Rect orig(posFrame, spritSize);
    SDL2pp::Rect dest(position, spritSize);
    renderer.Copy(
            texture,
            orig,
            dest,
            0,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flip
    );
}
