//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_BUTTONCONSTRUCTIONYARDCL_H
#define DUNE_BUTTONCONSTRUCTIONYARDCL_H


#include "../../ButtonCL.h"

class ButtonConstructionYardCL : public ButtonCL {
public:
    ButtonConstructionYardCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonConstructionYardCL() {}
};


#endif //DUNE_BUTTONCONSTRUCTIONYARDCL_H
