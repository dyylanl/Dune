//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrapCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonWidtrapCL::ButtonWidtrapCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
: ButtonCL(BWIND_TRAP, SDL2pp::Point(1089, 120), id, player, constructionTime, selectStatus, ready) {}

void ButtonWidtrapCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 3;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}