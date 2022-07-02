//
// Created by riclui on 26/06/22.
//

#include "ButtonSiloCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonSiloCL::ButtonSiloCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonBuildCL(BSILO, SDL2pp::Point(1114, 642), id, SILO_KEY,player, constructionTime, selectStatus, ready) {}

void ButtonSiloCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 5;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}

void ButtonSiloCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    ButtonCL::draw(renderer, textureManager);
    if(m_selectStatus && m_ready) {
        textureManager.draw(renderer, SILO, m_positionBuild,SDL2pp::Point(99,89));
    }
}
