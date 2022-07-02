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

void Vehicle::update(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        SDL_Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point(event.motion.x, event.motion.y);
        if (SDL_PointInRect(&point, &shape)) {
            std::unique_ptr<CommandCL> command(new SelectCL(m_id));
            std::cout << "Push command Select" << std::endl;
            queue.push(std::move(command));
        }
    }

    if (event.button.button == SDL_BUTTON_RIGHT && m_selectStatus) {
        SDL2pp::Point point(event.motion.x, event.motion.y);
        std::unique_ptr<CommandCL> command (new MoveCL(m_id, point));
        std::cout << "Push command Move" << std::endl;
        queue.push(std::move(command));
    }
}
