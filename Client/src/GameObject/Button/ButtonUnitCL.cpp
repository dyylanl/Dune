//
// Created by riclui on 27/06/22.
//

#include "ButtonUnitCL.h"
#include "../../Action/SelectCL.h"
#include "../../Action/CreateUniTCL.h"

ButtonUnitCL::ButtonUnitCL(char textureID, SDL2pp::Point position, int id, char type,char player, int actionTime,
                           bool selectStatus, bool ready)
        : ButtonCL(textureID, position, id, type, player, actionTime, selectStatus, ready) {}

void ButtonUnitCL::update(EventManager &eventManager, BQueue<std::unique_ptr<CommandCL>> &queue) {
    if (eventManager.mouseButtonDown(LEFT) && !m_selectStatus) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            std::unique_ptr<CommandCL> command(new CreateUniTCL(m_type));
            std::cout << "Push commando Select" << std::endl;
            queue.push(std::move(command));
        }
    }
}
