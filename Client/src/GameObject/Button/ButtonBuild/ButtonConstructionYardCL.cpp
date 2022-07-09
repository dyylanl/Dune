//
// Created by riclui on 23/06/22.
//

#include "ButtonConstructionYardCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonConstructionYardCL::ButtonConstructionYardCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
: ButtonBuildCL(BCONSTRUCTION_YARD, SDL2pp::Point(1114, 292), id, CONSTRUCTION_CENTER_KEY,player, constructionTime, selectStatus, ready),
  m_build(0,0,SDL2pp::Point(0, 0),0){}

void ButtonConstructionYardCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    std::unique_ptr<CommandCL> command(new BuildBuilding(m_type, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}

void ButtonConstructionYardCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Camera cam(SDL2pp::Point(0,0));
    ButtonCL::draw(renderer, textureManager, cam);
    if(m_selectStatus && m_ready) {
        m_build.setPosition(m_positionBuild);
        m_build.draw(renderer, textureManager, cam);
    }
}
