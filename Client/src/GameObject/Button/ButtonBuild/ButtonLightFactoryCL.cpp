//
// Created by riclui on 26/06/22.
//

#include "ButtonLightFactoryCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonLightFactoryCL::ButtonLightFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonCL(BLIGHT_FACTORY, SDL2pp::Point(1114, 432), id, player, constructionTime, selectStatus, ready) {}

void ButtonLightFactoryCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 1;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}
