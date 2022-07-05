//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONREFINERYCL_H
#define DUNE_BUTTONREFINERYCL_H


#include "../ButtonBuildCL.h"
#include "../../Builds/RefineryCL.h"

class ButtonRefineryCL : public ButtonBuildCL {
    RefineryCL m_build;
public:
    ButtonRefineryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonRefineryCL() {}
};


#endif //DUNE_BUTTONREFINERYCL_H
