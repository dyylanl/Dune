//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONSILO_H
#define DUNE_BUTTONSILO_H


#include "../Button.h"

class ButtonSilo : public Button {
public:
    ButtonSilo(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONSILO_H
