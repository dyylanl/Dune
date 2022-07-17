//
// Created by riclui on 30/05/22.
//

#include "TextureManager.h"
#include "../../includes/Client.h"

#define TILESIZE 30

#include <map>
#include <string>
#include <iterator>

void TextureManager::load(char id, std::string filename) {
    std::unique_ptr<SDL2pp::Texture> texture(new SDL2pp::Texture(m_renderer,SDL2pp::Surface(filename).SetColorKey(true, 0)));
    m_TextureMap.insert(std::pair{id,std::move(texture)});
}

TextureManager::TextureManager(SDL2pp::Renderer &renderer) : m_renderer(renderer){
}

void
TextureManager::drawFrame(SDL2pp::Renderer &renderer, char id, SDL2pp::Point position, SDL2pp::Point spritSize,
                          SDL2pp::Point posFrame, Camera &camera, int &player) {
    SDL2pp::Rect orig(posFrame, spritSize);
    SDL2pp::Rect dest(position, spritSize);
    if (player == 0) {
        m_TextureMap[id]->SetColorMod(255,255,0);
    }
    switch (player) {
        case 0: m_TextureMap[id]->SetColorMod(0,0,255);
            break;
        case 1: m_TextureMap[id]->SetColorMod(255,0,0);
            break;
        case 2: m_TextureMap[id]->SetColorMod(0,255,0);
            break;
        default: m_TextureMap[id]->SetColorMod(255,255,255);
    }
    renderer.Copy(*m_TextureMap[id],orig,dest + camera.getPosicion(),0,SDL2pp::NullOpt,SDL_FLIP_NONE);
}

void
TextureManager::draw(SDL2pp::Renderer &renderer, char id, SDL2pp::Point position, SDL2pp::Point size) {
    SDL2pp::Rect orig(SDL2pp::Point(0,0), size);
    SDL2pp::Rect dest(position, size);
    renderer.Copy(*m_TextureMap[id],orig,dest,0,SDL2pp::NullOpt);
}

void
TextureManager::drawTile(SDL2pp::Renderer &renderer, char id, SDL2pp::Point position, SDL2pp::Point size) {
    SDL2pp::Rect orig(SDL2pp::Point(0,0), size);
    SDL2pp::Rect dest(position, size);
    renderer.Copy(*m_TextureMap[id],orig,dest,0,SDL2pp::NullOpt,SDL_FLIP_NONE);
}

void TextureManager::drawMap(SDL2pp::Renderer &renderer, std::vector<std::vector<char>> &map, Camera &camera) {
    SDL2pp::Point size(TILESIZE, TILESIZE);
    for (int i = 0; i < (int) map.size(); ++i) {
        for (int j = 0; j < (int) map[0].size(); ++j) {
            char key = map[i][j];
            switch (key) {
                case 'A':
                    drawTile(renderer, ARENA, SDL2pp::Point(j * TILESIZE, i * TILESIZE) + camera.getPosicion(), size);
                    break;
                case 'P':
                    drawTile(renderer, PRECIPICIO, SDL2pp::Point(j * TILESIZE, i * TILESIZE) + camera.getPosicion(), size);
                    break;
                case 'R':
                    drawTile(renderer, ROCA, SDL2pp::Point(j * TILESIZE, i * TILESIZE) + camera.getPosicion(), size);
                    break;
                case 'D':
                    drawTile(renderer, DUNA, SDL2pp::Point(j * TILESIZE, i * TILESIZE) + camera.getPosicion(), size);
                    break;
                case 'C':
                    drawTile(renderer, CIMA, SDL2pp::Point(j * TILESIZE, i * TILESIZE) + camera.getPosicion(), size);
                    break;
            }
        }
    }
}

TextureManager::~TextureManager() {}
