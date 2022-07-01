//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONHEAVYFACTORYCL_H
#define DUNE_BUTTONHEAVYFACTORYCL_H


#include "../ButtonBuildCL.h"

class ButtonHeavyFactoryCL : public ButtonBuildCL {
public:
    ButtonHeavyFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonHeavyFactoryCL() {}
};


#endif //DUNE_BUTTONHEAVYFACTORYCL_H
