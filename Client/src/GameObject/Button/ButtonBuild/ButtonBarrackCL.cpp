//
// Created by riclui on 26/06/22.
//

#include "ButtonBarrackCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonBarrackCL::ButtonBarrackCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonCL(BBARRACK, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}

void ButtonBarrackCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 6;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}
