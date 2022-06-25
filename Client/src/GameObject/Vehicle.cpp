//
// Created by riclui on 22/06/22.
//

#include "Vehicle.h"
#include "../Action/SelectCL.h"
#include "../Action/MoveCL.h"

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
