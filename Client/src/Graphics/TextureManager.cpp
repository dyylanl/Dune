//
// Created by riclui on 30/05/22.
//

#include "TextureManager.h"

#define TILESIZE 50

void TextureManager::load(std::string id, std::string filename) {
    m_TextureMap[id] = filename;
}

TextureManager::TextureManager(SDL2pp::Renderer &renderer, Camera &camera) : m_renderer(renderer), camera(camera){
}

void
TextureManager::drawFrame(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point spritSize, SDL_RendererFlip flip) {
    SDL2pp::Texture texture(m_renderer,SDL2pp::Surface(m_TextureMap[id]).SetColorKey(true, 0));
    SDL2pp::Point posFrame(0,0);
    SDL2pp::Rect orig(posFrame, spritSize);
    SDL2pp::Rect dest(position - camera.getPosicion(), spritSize);
    renderer.Copy(texture,orig,dest,0,SDL2pp::NullOpt,flip);
}

void
TextureManager::draw(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point size, SDL_RendererFlip flip) {
    SDL2pp::Texture texture(m_renderer,SDL2pp::Surface(m_TextureMap[id]).SetColorKey(true, 0));
    SDL2pp::Rect orig(SDL2pp::Point(0,0), size);
    SDL2pp::Rect dest(position, size);
    renderer.Copy(texture,orig,dest,0,SDL2pp::NullOpt,flip);
}

Camera &TextureManager::getCamera() {
    return camera;
}

void
TextureManager::drawTile(SDL2pp::Renderer &renderer, const std::string id, SDL2pp::Point position, SDL2pp::Point size) {
    SDL2pp::Texture texture(m_renderer,SDL2pp::Surface(m_TextureMap[id]).SetColorKey(true, 0));
    SDL2pp::Rect orig(SDL2pp::Point(0,0), size);
    SDL2pp::Rect dest(position - camera.getPosicion(), size);
    renderer.Copy(texture,orig,dest,0,SDL2pp::NullOpt,SDL_FLIP_NONE);
}

void TextureManager::drawMap(SDL2pp::Renderer &renderer, std::vector<std::vector<char>> &map) {
    SDL2pp::Point size(TILESIZE, TILESIZE);
    for (int i = 0; i < (int) map.size(); ++i) {
        for (int j = 0; j < (int) map[0].size(); ++j) {
            char key = map[i][j];
            switch (key) {
                case 'A':
                    drawTile(renderer, "arena", SDL2pp::Point(j * TILESIZE, i * TILESIZE), size);
                    break;
                case 'P':
                    drawTile(renderer, "precipicio", SDL2pp::Point(j * TILESIZE, i * TILESIZE), size);
                    break;
                case 'R':
                    drawTile(renderer, "roca", SDL2pp::Point(j * TILESIZE, i * TILESIZE), size);
                    break;
                case 'D':
                    drawTile(renderer, "duna", SDL2pp::Point(j * TILESIZE, i * TILESIZE), size);
                    break;
                case 'C':
                    drawTile(renderer, "cima", SDL2pp::Point(j * TILESIZE, i * TILESIZE), size);
                    break;
            }
        }
    }
}
