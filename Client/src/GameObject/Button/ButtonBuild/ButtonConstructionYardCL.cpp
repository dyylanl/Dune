//
// Created by riclui on 23/06/22.
//

#include "ButtonConstructionYardCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonConstructionYardCL::ButtonConstructionYardCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
: ButtonCL(BCONSTRUCTION_YARD, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}

void ButtonConstructionYardCL::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 0;
    CommandCL *command = new BuildBuilding(build, point);
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}
