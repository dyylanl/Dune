//
// Created by riclui on 26/06/22.
//

#include "ButtonSiloCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonSiloCL::ButtonSiloCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonCL(BSILO, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}

void ButtonSiloCL::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 5;
    CommandCL *command = new BuildBuilding(build, point);
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}
