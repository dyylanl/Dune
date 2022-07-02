//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrapCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonWidtrapCL::ButtonWidtrapCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
: ButtonBuildCL(BWIND_TRAP, SDL2pp::Point(1114, 292), id, WIND_TRAP_KEY,player, constructionTime, selectStatus, ready) {}

void ButtonWidtrapCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    char build = 3;
    std::unique_ptr<CommandCL> command(new BuildBuilding(build, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(std::move(command));
}

void ButtonWidtrapCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    ButtonCL::draw(renderer, textureManager);
    if(m_selectStatus && m_ready) {
        textureManager.draw(renderer, WIND_TRAP, m_positionBuild,SDL2pp::Point(99,89));
    }
}
