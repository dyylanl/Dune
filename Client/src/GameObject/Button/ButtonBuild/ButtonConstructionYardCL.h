//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_BUTTONCONSTRUCTIONYARDCL_H
#define DUNE_BUTTONCONSTRUCTIONYARDCL_H


#include "../ButtonBuildCL.h"
#include "../../Builds/ConstructionYardCL.h"

class ButtonConstructionYardCL : public ButtonBuildCL {
private:
    ConstructionYardCL m_build;
public:
    ButtonConstructionYardCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonConstructionYardCL() {}
};


#endif //DUNE_BUTTONCONSTRUCTIONYARDCL_H
