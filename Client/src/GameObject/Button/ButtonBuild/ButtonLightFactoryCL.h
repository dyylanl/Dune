//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONLIGHTFACTORYCL_H
#define DUNE_BUTTONLIGHTFACTORYCL_H


#include "../ButtonBuildCL.h"

class ButtonLightFactoryCL : public ButtonBuildCL {
public:
    ButtonLightFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonLightFactoryCL() {}
};


#endif //DUNE_BUTTONLIGHTFACTORYCL_H
