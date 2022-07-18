//
// Created by riclui on 22/06/22.
//

#include "Vehicle.h"
#include "../Action/SelectCL.h"
#include "../Action/MoveCL.h"

Vehicle::Vehicle(char textureID, SDL2pp::Point position, SDL2pp::Point size, int id, int player, bool selecStatus,
                 SDL2pp::Point posAction, int life, bool action, int frameCount, int colCount)
                 : GameObject(textureID, position, size), m_id(id), m_player(player), m_selectStatus(selecStatus),
                 m_posAction(posAction), m_life(life), m_action(action),
                 m_animation(frameCount, colCount, m_size, m_position, m_posAction, m_player, m_life, m_selectStatus, m_action){}

void Vehicle::processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera,
                           SoundManager &soundManager) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point(event.motion.x - camera.getPosicion().GetX(), event.motion.y - camera.getPosicion().GetY());
        if (SDL_PointInRect(&point, &shape)) {
            std::unique_ptr<CommandCL> command(new SelectCL(point));
            std::cout << "Push command Select" << std::endl;
            queue.push(command);
            soundManager.playEffect("unit_selected");
        }
    }
}

void Vehicle::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    m_animation.draw(renderer, textureManager, m_textureID, camera);
}
