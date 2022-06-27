//
// Created by riclui on 22/06/22.
//

#include "ButtonCL.h"
#include "../Action/SelectCL.h"

ButtonCL::ButtonCL(char textureID, SDL2pp::Point position, int id, char player, int constructionTime, bool selectStatus, bool ready)
        : GameObject(textureID, position, SDL2pp::Point(66, 66)), m_id(id), m_player(player)
        , m_constructionTime(constructionTime), m_selectStatus(selectStatus), m_ready(ready) {}

void ButtonCL::update(EventManager &eventManager, BlockingQueue<CommandCL *> &queue) {
    if (eventManager.mouseButtonDown(LEFT) && !m_selectStatus) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            CommandCL *command = new SelectCL(m_id);
            std::cout << "Push commando Select" << std::endl;
            queue.push(command);
        }
    }

    if (eventManager.mouseButtonDown(RIGHT) && m_selectStatus && m_ready) {
        SDL2pp::Point point = eventManager.getMouse();
        buildBuilding(queue, point);
    }
}

void ButtonCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}
