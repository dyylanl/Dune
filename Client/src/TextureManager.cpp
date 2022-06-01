//
// Created by riclui on 30/05/22.
//

#include "TextureManager.h"

void TextureManager::load(std::string &id, std::string &filename) {
    /*SDL2pp::Texture texture(m_renderer,
              SDL2pp::Surface(filename).SetColorKey(true, 0));*/
    m_TextureMap[id] = filename;
}

TextureManager::TextureManager(SDL2pp::Renderer &renderer) : m_renderer(renderer){
}

void TextureManager::draw(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Rect orig, const SDL2pp::Rect dest,
                          double rotacion, SDL_RendererFlip flip) {
    SDL2pp::Texture texture(m_renderer,
                            SDL2pp::Surface(m_TextureMap[id]).SetColorKey(true, 0));
    renderer.Copy(
            texture,
            orig,
            dest,
            rotacion,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flip
    );
}
