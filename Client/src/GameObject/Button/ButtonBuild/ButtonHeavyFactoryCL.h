//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONHEAVYFACTORYCL_H
#define DUNE_BUTTONHEAVYFACTORYCL_H


#include "../ButtonBuildCL.h"
#include "../../Builds/HeavyFactoryCL.h"

class ButtonHeavyFactoryCL : public ButtonBuildCL {
private:
    HeavyFactoryCL m_build;
public:
    ButtonHeavyFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonHeavyFactoryCL() {}
};


#endif //DUNE_BUTTONHEAVYFACTORYCL_H
