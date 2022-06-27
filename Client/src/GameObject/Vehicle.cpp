//
// Created by riclui on 22/06/22.
//

#include "Vehicle.h"
#include "../Action/SelectCL.h"
#include "../Action/MoveCL.h"

Vehicle::Vehicle(char textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, bool selecStatus,
                 SDL2pp::Point posAction, int life, bool action)
                 : GameObject(textureID, position, size), m_id(id), m_player(player), m_selectStatus(selecStatus),
                 m_posAction(posAction), m_life(life), m_action(action) {}

void Vehicle::update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue) {
    if (eventManager.mouseButtonDown(LEFT)) {
        SDL_Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL_Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            CommandCL *command = new SelectCL(m_id);
            std::cout << "Push command Select" << std::endl;
            queue.push(command);
        }
    }

    if (eventManager.mouseButtonDown(RIGHT) && m_selectStatus) {
        CommandCL *command = new MoveCL(m_id, eventManager.getMouse());
        std::cout << "Push command Move" << std::endl;
        queue.push(command);
    }
}
