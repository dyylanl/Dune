//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_TEXTUREMANAGER_H
#define DUNE_TEXTUREMANAGER_H


#include "SDL2pp/SDL2pp.hh"
#include "../Camera/Camera.h"
#include <map>

class TextureManager {
private:
    SDL2pp::Renderer &m_renderer;
    std::map<std::string, std::string> m_TextureMap;
    Camera camera;

public:
    TextureManager(SDL2pp::Renderer &renderer, Camera &camera);

    void load(std::string id, std::string filename);

    void drawFrame(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point spritSize, SDL_RendererFlip flip);

    void draw(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point size, SDL_RendererFlip flip);

    void drawMap(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point size, SDL_RendererFlip flip);

    Camera& getCamera();
};


#endif //DUNE_TEXTUREMANAGER_H
