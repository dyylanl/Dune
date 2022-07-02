//
// Created by riclui on 30/06/22.
//

#include "ButtonBuildCL.h"
#include "../../Action/SelectCL.h"
#include "../Builds/SiloCL.h"

ButtonBuildCL::ButtonBuildCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime,
                             bool selectStatus, bool ready) : ButtonCL(textureID, position, id, type, player, actionTime,
                                                                     selectStatus, ready) {}

void ButtonBuildCL::update(EventManager &eventManager, BQueue<std::unique_ptr<CommandCL>> &queue) {
    if(eventManager.mouseButtonDown(LEFT) && !m_selectStatus && !m_ready) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            std::cout << "Inicia timer" << std::endl;
            std::cout << "Listo" << std::endl;
            m_ready = true;

            /*unsigned int initTime = SDL_GetTicks();
            std::unique_ptr<CommandCL> command(new SelectCL(m_id));
            std::cout << "Push commando Select" << std::endl;
            queue.push(std::move(command));*/
        }
    }

    if (eventManager.mouseButtonDown(LEFT) && !m_selectStatus && m_ready) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            m_selectStatus = true;
            /*unsigned int initTime = SDL_GetTicks();
            std::unique_ptr<CommandCL> command(new SelectCL(m_id));
            std::cout << "Push commando Select" << std::endl;
            queue.push(std::move(command));*/
        }
    }

    if (m_selectStatus && m_ready) {
        m_positionBuild = eventManager.getMouse();
    }

    if (eventManager.mouseButtonDown(RIGHT) && m_selectStatus && m_ready) {
        m_selectStatus = false;
        SDL2pp::Point point = eventManager.getMouse();
        buildBuilding(queue, point);
    }
}
