//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_TEXTUREMANAGER_H
#define DUNE_TEXTUREMANAGER_H


#include <SDL2pp/SDL2pp.hh>
#include <map>

class TextureManager {
private:
    SDL2pp::Renderer &m_renderer;
    std::map<std::string, SDL2pp::Texture*> m_TextureMap;

public:
    TextureManager(SDL2pp::Renderer &renderer);

    void load(std::string id, std::string filename);
};


#endif //DUNE_TEXTUREMANAGER_H
