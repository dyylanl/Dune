//
// Created by riclui on 26/06/22.
//

#include "ButtonPalaceCL.h"
#include "../../../Action/BuildBuilding.h"

ButtonPalaceCL::ButtonPalaceCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonBuildCL(BPALACE, SDL2pp::Point(1114, 502), id, PALACE_KEY,player, constructionTime, selectStatus, ready),
        m_build(0,-1,SDL2pp::Point(0, 0),0) {}

void ButtonPalaceCL::buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) {
    std::unique_ptr<CommandCL> command(new BuildBuilding(m_type, point));
    std::cout << "Push command BuildBuilding" << std::endl;
    queue.push(command);
}

void ButtonPalaceCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Camera cam(SDL2pp::Point(0,0));
    ButtonCL::draw(renderer, textureManager, cam);
    if(m_selectStatus && m_ready) {
        m_build.setPosition(m_positionBuild);
        m_build.draw(renderer, textureManager, cam);
    }
}
