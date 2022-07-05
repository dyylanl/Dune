//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONWIDTRAPCL_H
#define DUNE_BUTTONWIDTRAPCL_H


#include "../ButtonBuildCL.h"
#include "../../Builds/WindTrapCL.h"

class ButtonWidtrapCL : public ButtonBuildCL{
private:
    WindTrapCL m_build;
public:
    ButtonWidtrapCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonWidtrapCL() {}
};


#endif //DUNE_BUTTONWIDTRAPCL_H
