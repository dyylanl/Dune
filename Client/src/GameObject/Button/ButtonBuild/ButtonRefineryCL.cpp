//
// Created by riclui on 20/06/22.
//

#include "ButtonRefineryCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonRefineryCL::ButtonRefineryCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonBuildCL(BREFINERY, SDL2pp::Point(1114, 572), id, REFINERY_KEY, player, constructionTime, selectStatus, ready) {}

void ButtonRefineryCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 4;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}