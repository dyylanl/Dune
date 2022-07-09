//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrapCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonWidtrapCL::ButtonWidtrapCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
: ButtonBuildCL(BWIND_TRAP, SDL2pp::Point(1114, 292), id, WIND_TRAP_KEY,player, constructionTime, selectStatus, ready),
  m_build(0,0,SDL2pp::Point(0, 0),0){}

void ButtonWidtrapCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    std::unique_ptr<CommandCL> command(new BuildBuilding(m_type, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}

void ButtonWidtrapCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Camera cam(SDL2pp::Point(0,0));
    ButtonCL::draw(renderer, textureManager, cam);
    if(m_selectStatus && m_ready) {
        m_build.setPosition(m_positionBuild);
        m_build.draw(renderer, textureManager, cam);
    }
}
