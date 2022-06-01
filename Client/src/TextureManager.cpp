//
// Created by riclui on 30/05/22.
//

#include "TextureManager.h"

void TextureManager::load(std::string id, std::string filename) {
    SDL2pp::Texture texture(m_renderer,
              SDL2pp::Surface(filename).SetColorKey(true, 0));
    m_TextureMap[id] = &texture;
}

TextureManager::TextureManager(SDL2pp::Renderer &renderer) : m_renderer(renderer){
}
