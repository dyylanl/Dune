//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_TEXTUREMANAGER_H
#define DUNE_TEXTUREMANAGER_H


#include "SDL2pp/SDL2pp.hh"
#include "../Camera/Camera.h"
#include <map>
#include <memory>

class TextureManager {
private:
    SDL2pp::Renderer &m_renderer;
    std::map<char, std::unique_ptr<SDL2pp::Texture>> m_TextureMap;

public:
    TextureManager(SDL2pp::Renderer &renderer);

    void load(char id, std::string filename);

    void drawFrame(SDL2pp::Renderer &renderer, char id, SDL2pp::Point position, SDL2pp::Point spritSize,
                   SDL2pp::Point posFrame, Camera &camera, int &player);

    void draw(SDL2pp::Renderer &renderer, char id, SDL2pp::Point position, SDL2pp::Point size);

    void drawTile(SDL2pp::Renderer &renderer, char id, SDL2pp::Point position, SDL2pp::Point size);

    void drawMap(SDL2pp::Renderer &renderer, std::vector<std::vector<char>> &map, Camera &camera);

    ~TextureManager();
};


#endif //DUNE_TEXTUREMANAGER_H
