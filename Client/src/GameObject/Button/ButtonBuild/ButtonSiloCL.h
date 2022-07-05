//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONSILOCL_H
#define DUNE_BUTTONSILOCL_H


#include "../ButtonBuildCL.h"
#include "../../Builds/SiloCL.h"

class ButtonSiloCL : public ButtonBuildCL{
private:
    SiloCL m_build;
public:
    ButtonSiloCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonSiloCL() {}
};


#endif //DUNE_BUTTONSILOCL_H
