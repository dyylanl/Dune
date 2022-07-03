//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONPALACECL_H
#define DUNE_BUTTONPALACECL_H


#include "../ButtonBuildCL.h"
#include "../../Builds/PalaceCL.h"

class ButtonPalaceCL : public ButtonBuildCL {
private:
    PalaceCL m_build;
public:
    ButtonPalaceCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonPalaceCL() {}
};


#endif //DUNE_BUTTONPALACECL_H
