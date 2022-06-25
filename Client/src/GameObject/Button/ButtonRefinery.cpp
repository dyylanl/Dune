//
// Created by riclui on 20/06/22.
//

#include "ButtonRefinery.h"
#include "../../Action/BuildBuilding.h"

ButtonRefinery::ButtonRefinery(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : Button("ButtonRefinery", SDL2pp::Point(1089, 120),id, player, constructionTime, selectStatus, ready) {}

void ButtonRefinery::buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point) {
    char build = 4;
    CommandCL *command = new BuildBuilding(build, point);
    queue.push(command);
}