//
// Created by riclui on 26/06/22.
//

#include "ButtonBarrack.h"
#include "../../Action/BuildBuilding.h"

ButtonBarrack::ButtonBarrack(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : Button("ButtonConstructionYard", SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}

void ButtonBarrack::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 6;
    CommandCL *command = new BuildBuilding(build, point);
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}
