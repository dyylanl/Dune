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

void Vehicle::processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point(event.motion.x, event.motion.y);
        if (SDL_PointInRect(&point, &shape)) {
            std::unique_ptr<CommandCL> command(new SelectCL(point - camera.getPosicion()));
            std::cout << "Push command Select" << std::endl;
            queue.push(command);
        }
    }
}

void Vehicle::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::Point posFrame(0,0);
    if(m_selectStatus) {
        textureManager.drawFrame(renderer, LIFE, m_position - SDL2pp::Point(0,10), SDL2pp::Point(40,8), SDL2pp::Point(0,0), camera);
    }
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame, camera);
}
