//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrap.h"
#include "../../Action/BuildBuilding.h"

ButtonWidtrap::ButtonWidtrap(int id, char player, int constructionTime, bool selectStatus, bool ready)
: Button(BWIND_TRAP, SDL2pp::Point(1089, 120), id, player, constructionTime, selectStatus, ready) {}

void ButtonWidtrap::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 3;
    CommandCL *command = new BuildBuilding(build, point);
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}