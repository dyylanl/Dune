//
// Created by riclui on 20/06/22.
//

#include "ButtonRefineryCL.h"
#include "../../Action/BuildBuilding.h"

ButtonRefineryCL::ButtonRefineryCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonBuild(BREFINERY, SDL2pp::Point(1089, 120), id, player, constructionTime, selectStatus, ready) {}

void ButtonRefineryCL::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 4;
    CommandCL *command = new BuildBuilding(build, point);
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}