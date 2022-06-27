//
// Created by riclui on 26/06/22.
//

#include "ButtonPalaceCL.h"
#include "../../Action/BuildBuilding.h"

ButtonPalaceCL::ButtonPalaceCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonBuild(BPALACE, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}

void ButtonPalaceCL::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 7;
    CommandCL *command = new BuildBuilding(build, point);
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}
