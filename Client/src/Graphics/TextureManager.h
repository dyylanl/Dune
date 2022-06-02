//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_TEXTUREMANAGER_H
#define DUNE_TEXTUREMANAGER_H


#include "SDL2pp/SDL2pp.hh"
#include <map>

class TextureManager {
private:
    SDL2pp::Renderer &m_renderer;
    std::map<std::string, std::string> m_TextureMap;

public:
    TextureManager(SDL2pp::Renderer &renderer);

    void load(std::string id, std::string filename);

    void
    draw(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Rect orig, const SDL2pp::Rect dest, double rotacion, SDL_RendererFlip flip);
};


#endif //DUNE_TEXTUREMANAGER_H
