//
// Created by riclui on 30/06/22.
//

#include "ButtonBuildCL.h"
#include "../../Action/SelectCL.h"
#include "../Builds/SiloCL.h"

ButtonBuildCL::ButtonBuildCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime,
                             bool selectStatus, bool ready) : ButtonCL(textureID, position, id, type, player, actionTime,
                                                                     selectStatus, ready) {}

void ButtonBuildCL::processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera) {
    if(event.button.button == SDL_BUTTON_LEFT && !m_selectStatus && !m_ready) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point(event.motion.x, event.motion.y);
        if (SDL_PointInRect(&point, &shape)) {
            std::cout << "Inicia timer" << std::endl;
            std::cout << "Listo" << std::endl;
            m_ready = true;
        }
    }

    if (event.button.button == SDL_BUTTON_LEFT && !m_selectStatus && m_ready) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point(event.motion.x, event.motion.y);
        if (SDL_PointInRect(&point, &shape)) {
            m_selectStatus = true;
        }
    }

    if (m_selectStatus && m_ready) {
        m_positionBuild = SDL2pp::Point(event.motion.x, event.motion.y);;
    }

    if (event.button.button == SDL_BUTTON_RIGHT && m_selectStatus && m_ready) {
        m_selectStatus = false;
        SDL2pp::Point point(event.motion.x, event.motion.y);
        buildBuilding(queue, point - camera.getPosicion());
    }
}
