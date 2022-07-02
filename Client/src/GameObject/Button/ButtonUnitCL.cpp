//
// Created by riclui on 27/06/22.
//

#include "ButtonUnitCL.h"
#include "../../Action/SelectCL.h"
#include "../../Action/CreateUniTCL.h"

ButtonUnitCL::ButtonUnitCL(char textureID, SDL2pp::Point position, int id, char type,char player, int actionTime,
                           bool selectStatus, bool ready)
        : ButtonCL(textureID, position, id, type, player, actionTime, selectStatus, ready) {}

void ButtonUnitCL::processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !m_selectStatus) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point(event.motion.x, event.motion.y);
        if (SDL_PointInRect(&point, &shape)) {
            std::unique_ptr<CommandCL> command(new CreateUniTCL(m_type));
            std::cout << "Push commando Create Unit" << std::endl;
            queue.push(std::move(command));
        }
    }
}
