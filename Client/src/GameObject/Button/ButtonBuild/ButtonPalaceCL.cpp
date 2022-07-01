//
// Created by riclui on 26/06/22.
//

#include "ButtonPalaceCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonPalaceCL::ButtonPalaceCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonBuildCL(BPALACE, SDL2pp::Point(1114, 502), id, PALACE_KEY,player, constructionTime, selectStatus, ready) {}

void ButtonPalaceCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 7;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}
