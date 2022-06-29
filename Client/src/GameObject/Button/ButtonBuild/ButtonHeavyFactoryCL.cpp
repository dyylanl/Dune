//
// Created by riclui on 26/06/22.
//

#include "ButtonHeavyFactoryCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonHeavyFactoryCL::ButtonHeavyFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonCL(BHEAVY_FACTORY, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}

void ButtonHeavyFactoryCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 2;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}
